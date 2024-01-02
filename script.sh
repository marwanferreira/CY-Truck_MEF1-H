#!/bin/bash

# Check if at least one argument is provided
if [ $# -lt 1 ]; then
    echo "Usage: $0 data.csv [-r]"
    exit 1
fi

# Check for help argument
if [ "$1" == "-h" ]; then
    echo "Usage information..."
    exit 0
fi

# Check if CSV file exists
if [ ! -f "$1" ]; then
    echo "Error: CSV file not found."
    exit 1
fi

csv_file="$1"  # Initialize csv_file variable

# Ensure temp and output directories exist
mkdir -p temp
mkdir -p output  # Create output directory
rm -rf temp/*  # Clear the temp directory

# Process additional options (like -d1, -d2, etc.)
shift # Skip the first argument (CSV file)
while (( "$#" )); do
    case "$1" in
        -d1)
            SECONDS=0  # Reset timer
            awk -F, '{print $6}' "$csv_file" | sort | uniq -c | sort -nr | head -10 > temp/d1_output.txt
            duration=$SECONDS
            echo "Processing for -d1 took $duration seconds."
            gnuplot -e "plot 'temp/d1_output.txt' using 1:2 with lines" > output/d1_graph.png
            # Use GnuPlot to create a horizontal histogram from temp/d1_output.txt
            ;;
        -d2)
            SECONDS=0  # Reset timer
            # Your data processing commands
            awk -F, '{distance[$6]+=$5} END {...}' "$csv_file" | sort -k2 -nr | head -10 > temp/d2_output.txt
            duration=$SECONDS
            echo "Processing for -d2 took $duration seconds."
            gnuplot -e "plot 'temp/d2_output.txt' using 1:2 with lines" > output/d2_graph.png
             # Use GnuPlot to create a horizontal histogram from temp/d2_output.txt
            ;;
        # Add more cases as needed
        *)
            # Unknown option
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
    shift
done


