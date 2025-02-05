#!/bin/bash
# test.sh - Advanced tester for the 42 School minitalk Project (Mandatory & Bonus)
# This script compiles the project, then launches the server (mandatory or bonus)
# and runs several tests (simple, long, Unicode, empty, multiple messages, rapid succession).
# It includes timing measurements and detailed output for each test.

# Global configuration
SERVER_LOG="server.log"
USE_NANOSECONDS=1

# --- Helper Functions ---

# Get current time in nanoseconds (or seconds if %N isn't supported)
get_time() {
    local t
    t=$(date +%s%N 2>/dev/null)
    if [[ $t =~ [^0-9] ]]; then
        # Fallback: if %N produces non-digits, use seconds only.
        t=$(date +%s)
        USE_NANOSECONDS=0
    fi
    echo "$t"
}

# --- Core Functions ---

# Compile the project via Makefile
compile_project() {
    echo "Compiling project..."
    if [ ! -f Makefile ]; then
        echo "Makefile not found! Aborting."
        exit 1
    fi
    make re
    if [ $? -ne 0 ]; then
        echo "Compilation failed! Aborting tests."
        exit 1
    fi
    echo "Compilation successful!"
}

# Launch the server using the chosen executable in the background
launch_server() {
    local server_exec=$1
    echo "Starting the server ($server_exec)..."
    > "$SERVER_LOG"
    ./"$server_exec" > "$SERVER_LOG" 2>&1 &
    SERVER_PID=$!
    sleep 1
    echo "Server started with PID: $SERVER_PID"
}

# Stop the server gracefully
stop_server() {
    echo "Stopping server (PID: $SERVER_PID)..."
    kill -SIGTERM "$SERVER_PID" 2>/dev/null
    sleep 1
}

# Clear the server log before tests
clear_server_log() {
    > "$SERVER_LOG"
}

# Run a single test
# $1: test message to send
# $2: expected pattern in the server log (substring expected)
# $3: client executable (client or client_bonus)
run_test() {
    local test_msg="$1"
    local expected="$2"
    local client_exec="$3"

    echo "Sending message: $test_msg"
    clear_server_log

    local start_time end_time elapsed_ns elapsed_ms
    start_time=$(get_time)
    ./"$client_exec" "$SERVER_PID" "$test_msg"
    sleep 1
    end_time=$(get_time)

    if [ $USE_NANOSECONDS -eq 1 ]; then
        elapsed_ns=$((end_time - start_time))
        elapsed_ms=$((elapsed_ns / 1000000))
    else
        # Fallback to seconds resolution
        elapsed_ms=$(( (end_time - start_time) * 1000 ))
    fi

    if grep -q "$expected" "$SERVER_LOG"; then
        echo -e "Test result: \033[0;32m✅ PASS\033[0m (Time taken: ${elapsed_ms}ms)"
    else
        echo -e "Test result: \033[0;31m❌ FAIL\033[0m (Time taken: ${elapsed_ms}ms)"
        echo "Expected pattern: $expected"
        echo "Server log snippet:"
        head -n 3 "$SERVER_LOG"
    fi
}

# Run multiple consecutive messages test. Each message is expected in the server log.
run_multiple_messages() {
    local client_exec="$1"
    local messages=("First message" "Second message (42 rules)" "Third message!" "Final message")
    for msg in "${messages[@]}"; do
        run_test "$msg" "$msg" "$client_exec"
    done
}

# Run rapid-succession test: concurrently sends multiple messages and checks all are received.
run_rapid_succession_test() {
    local client_exec="$1"
    local messages=("Rapid1" "Rapid2" "Rapid3" "Rapid4" "Rapid5")
    clear_server_log
    echo "Running rapid succession test..."
    
    local start_time end_time elapsed_ns elapsed_ms
    start_time=$(get_time)
    for msg in "${messages[@]}"; do
        ./"$client_exec" "$SERVER_PID" "$msg" &
    done
    wait
    sleep 1
    end_time=$(get_time)

    if [ $USE_NANOSECONDS -eq 1 ]; then
        elapsed_ns=$((end_time - start_time))
        elapsed_ms=$((elapsed_ns / 1000000))
    else
        elapsed_ms=$(( (end_time - start_time) * 1000 ))
    fi

    local all_passed=true
    for msg in "${messages[@]}"; do
        if ! grep -q "$msg" "$SERVER_LOG"; then
            echo "Message '$msg' not received."
            all_passed=false
        fi
    done

    if $all_passed; then
        echo -e "Rapid succession test result: \033[0;32m✅ PASS\033[0m (Time taken: ${elapsed_ms}ms)"
    else
        echo -e "Rapid succession test result: \033[0;31m❌ FAIL\033[0m (Time taken: ${elapsed_ms}ms)"
        echo "Server log snippet:"
        head -n 5 "$SERVER_LOG"
    fi
}

# Display the interactive tester menu
show_menu() {
    echo "========================================"
    echo "   Minitalk Advanced Tester Menu"
    echo "========================================"
    echo "Test Mode: $TEST_MODE"
    echo "Using server: $SERVER_EXEC and client: $CLIENT_EXEC"
    echo "----------------------------------------"
    echo "1) Send simple message"
    echo "2) Send long message"
    echo "3) Send Unicode message"
    echo "4) Send empty message"
    echo "5) Send multiple consecutive messages"
    echo "6) Rapid succession messages test"
    echo "7) Change test mode (Mandatory/Bonus)"
    echo "8) Exit"
    echo -n "Choose an option [1-8]: "
}

# Let the user select the test mode (Mandatory or Bonus)
select_test_mode() {
    echo "Select test mode:"
    echo "1) Mandatory tests (using server & client)"
    echo "2) Bonus tests (using server_bonus & client_bonus)"
    read -r mode
    if [ "$mode" == "2" ]; then
        TEST_MODE="Bonus"
        SERVER_EXEC="server_bonus"
        CLIENT_EXEC="client_bonus"
    else
        TEST_MODE="Mandatory"
        SERVER_EXEC="server"
        CLIENT_EXEC="client"
    fi
}

# --- Main Script Flow ---

select_test_mode
compile_project
launch_server "$SERVER_EXEC"

while true; do
    show_menu
    read -r option
    case $option in
        1)
            run_test "Hello, minitalk!" "Hello, minitalk!" "$CLIENT_EXEC"
            ;;
        2)
            long_message=$(printf 'LongMessage '%.0s {1..50})
            run_test "$long_message" "LongMessage" "$CLIENT_EXEC"
            ;;
        3)
            unicode_message="Hello, 🌍! こんにちは世界！Привет мир!?"
            run_test "$unicode_message" "🌍" "$CLIENT_EXEC"
            ;;
        4)
            run_test "" "" "$CLIENT_EXEC"
            ;;
        5)
            run_multiple_messages "$CLIENT_EXEC"
            ;;
        6)
            run_rapid_succession_test "$CLIENT_EXEC"
            ;;
        7)
            stop_server
            select_test_mode
            launch_server "$SERVER_EXEC"
            ;;
        8)
            echo "Exiting tests..."
            stop_server
            exit 0
            ;;
        *)
            echo "Invalid option. Please choose between 1 and 8."
            ;;
    esac
    echo ""
done
