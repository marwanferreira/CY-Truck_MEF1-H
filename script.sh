#!/bin/bash

# Check if at least one argument is provided
if [ $# -lt 1 ]; then
    echo "Usage: $0 data_file.csv [options]"
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

echo "Creating temp and output directories if they don't already exist..."
mkdir -p temp
mkdir -p output
echo "Clearing the temp directory..."
rm -rf temp/*

# Process additional options (like -d1, -d2, etc.)
shift # Skip the first argument (CSV file)
while (( "$#" )); do
    case "$1" in
        -d1)
            echo "Processing for -d1..."
            SECONDS=0  # Reset timer
            awk -F, '{print $6}' "$csv_file" | sort | uniq -c | sort -nr | head -10 > temp/d1_output.txt
            duration=$SECONDS
            echo "Processing for -d1 took $duration seconds."
            gnuplot -e "set terminal png; set output 'output/d1_graph.png'; set style data histograms; set style fill solid; plot 'temp/d1_output.txt' using 2:xtic(1)" 
            echo "Histogram for -d1 generated."
            ;;
        -d2)
            echo "Processing for -d2..."
            SECONDS=0  # Reset timer
            awk -F, '{distance[$6]+=$5} END {for (driver in distance) print driver, distance[driver]}' "$csv_file" | sort -k2 -nr | head -10 > temp/d2_output.txt
            duration=$SECONDS
            echo "Processing for -d2 took $duration seconds."
            gnuplot -e "set terminal png; set output 'output/d2_graph.png'; set style data histograms; set style fill solid; plot 'temp/d2_output.txt' using 2:xtic(1) reverse" 
            echo "Histogram for -d2 generated."
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
    shift
done

echo "Script completed successfully."



