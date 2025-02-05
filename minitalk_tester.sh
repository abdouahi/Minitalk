#!/bin/bash
# minitalk-ultimate-tester.sh - Ultimate Tester for 42 Minitalk Project
# Features: Mandatory + Bonus tests, Detailed Reporting, Stress Tests, UI/UX

# =========================================
# Configuration
# =========================================
SERVER_LOG="server.log"
CLIENT_LOG="client.log"
TEST_LOGS_DIR="test_logs"
USE_COLORS=1
TIMEOUT=5  # seconds to wait for server response
STRESS_LENGTH=10000  # 10K characters for stress test
MAX_CONCURRENT_CLIENTS=50  # For bonus stress test

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# =========================================
# Helper Functions
# =========================================
print_header() {
    echo -e "${BLUE}\n========================================"
    echo -e "$1"
    echo -e "========================================${NC}"
}

print_result() {
    if [ "$1" == "success" ]; then
        echo -e "${GREEN}✓ $2${NC}"
    elif [ "$1" == "error" ]; then
        echo -e "${RED}✗ $2${NC}"
    else
        echo -e "${YELLOW}⚠ $2${NC}"
    fi
}

get_time_ms() {
    date +%s%3N
}

wait_for_pid() {
    local timeout=$TIMEOUT
    while [ ! -s "$SERVER_LOG" ] && [ $timeout -gt 0 ]; do
        sleep 0.1
        ((timeout -= 1))
    done
    if [ ! -s "$SERVER_LOG" ]; then
        echo -e "${RED}Server failed to start!${NC}"
        exit 1
    fi
    grep -m1 -Eo '[0-9]+' "$SERVER_LOG"
}

cleanup() {
    pkill -P $$ 2>/dev/null
    rm -f "$SERVER_LOG" "$CLIENT_LOG"
    [ -d "$TEST_LOGS_DIR" ] && rm -rf "$TEST_LOGS_DIR"
}

# =========================================
# Core Testing Functions
# =========================================
compile_project() {
    print_header "Compiling Project"
    make re >/dev/null 2>&1
    if [ $? -ne 0 ]; then
        print_result "error" "Compilation failed"
        exit 1
    fi
    print_result "success" "Compilation successful"
}

start_server() {
    local server_type=$1
    print_header "Starting $server_type Server"
    > "$SERVER_LOG"  # Clear the server log
    ./$server_type > "$SERVER_LOG" 2>&1 &
    SERVER_PID=$(wait_for_pid)
    if [ -z "$SERVER_PID" ]; then
        print_result "error" "Failed to get server PID"
        exit 1
    fi
    print_result "success" "Server PID: $SERVER_PID"
}

send_message() {
    local client=$1
    local msg="$2"
    local log_file="$TEST_LOGS_DIR/test_$(date +%s%N).log"
    
    echo "Sent:     '$msg'" > "$log_file"
    ./$client $SERVER_PID "$msg" >> "$log_file" 2>&1
    
    local start_time=$(get_time_ms)
    while true; do
        grep -q "$msg" "$SERVER_LOG" && break
        if [ $(($(get_time_ms) - start_time)) -gt $((TIMEOUT * 1000)) ]; then
            echo "Timeout waiting for message" >> "$log_file"
            return 1
        fi
        sleep 0.1
    done
    
    echo "Received: '$(grep -a "$msg" "$SERVER_LOG" | tail -1)'" >> "$log_file"
    return 0
}

# =========================================
# Test Cases
# =========================================
run_basic_tests() {
    local client=$1
    print_header "Running Basic Tests"
    
    # Test 1: Short message
    if send_message $client "Hello Minitalk!"; then
        print_result "success" "Short message test passed"
    else
        print_result "error" "Short message test failed"
    fi

    # Test 2: Empty message
    if send_message $client ""; then
        print_result "success" "Empty message test passed"
    else
        print_result "error" "Empty message test failed"
    fi

    # Test 3: Special characters
    if send_message $client "~!@#$%^&*()_+{}|:<>?[]\;',./"; then
        print_result "success" "Special chars test passed"
    else
        print_result "error" "Special chars test failed"
    fi
}

run_unicode_tests() {
    local client=$1
    print_header "Running Unicode Tests"
    
    local unicode_msgs=(
        "Hello 🌍 World"
        "こんにちは世界"
        "Привет мир"
        "مرحبا بالعالم"
        "😊✅🚀"
    )

    for msg in "${unicode_msgs[@]}"; do
        if send_message $client "$msg"; then
            print_result "success" "Unicode test: '$msg'"
        else
            print_result "error" "Unicode test failed: '$msg'"
        fi
    done
}

run_stress_tests() {
    local client=$1
    print_header "Running Stress Tests"
    
    # Generate random long string
    local stress_msg=$(head /dev/urandom | tr -dc A-Za-z0-9 | head -c $STRESS_LENGTH)
    
    # Test 1: Long message
    if send_message $client "$stress_msg"; then
        print_result "success" "Long message ($STRESS_LENGTH chars)"
    else
        print_result "error" "Long message test failed"
    fi

    # Test 2: High-speed messages
    local start_time=$(get_time_ms)
    for i in {1..100}; do
        send_message $client "Message $i" &
    done
    wait
    local duration=$(( $(get_time_ms) - start_time ))
    print_result "info" "100 messages in ${duration}ms"

    # Verify count
    local received_count=$(grep -c "Message [0-9]" "$SERVER_LOG")
    if [ $received_count -eq 100 ]; then
        print_result "success" "Received 100/100 messages"
    else
        print_result "error" "Lost $((100 - received_count)) messages"
    fi
}

run_bonus_tests() {
    print_header "Running Bonus Stress Test"
    
    local start_time=$(get_time_ms)
    for i in $(seq $MAX_CONCURRENT_CLIENTS); do
        ( ./client_bonus $SERVER_PID "Client $i: $(uuidgen)" ) &
    done
    wait
    
    local duration=$(( $(get_time_ms) - start_time ))
    local received_count=$(grep -c "Client [0-9]" "$SERVER_LOG")
    
    if [ $received_count -eq $MAX_CONCURRENT_CLIENTS ]; then
        print_result "success" "All $MAX_CONCURRENT_CLIENTS clients handled"
    else
        print_result "error" "Lost $((MAX_CONCURRENT_CLIENTS - received_count)) clients"
    fi
    print_result "info" "Bonus test completed in ${duration}ms"
}

# =========================================
# Main Execution
# =========================================
trap cleanup EXIT
mkdir -p "$TEST_LOGS_DIR"

# Compile and test mandatory
compile_project
start_server "server"
run_basic_tests "client"
run_unicode_tests "client"
run_stress_tests "client"
pkill -P $$

# Compile and test bonus
compile_project
start_server "server_bonus"
run_basic_tests "client_bonus"
run_unicode_tests "client_bonus"
run_stress_tests "client_bonus"
run_bonus_tests

print_header "Testing Complete"
echo -e "${GREEN}Check detailed logs in: $TEST_LOGS_DIR${NC}"
