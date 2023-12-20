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
mkdir -p temp  # Create temp directory
gnuplot -e "plot 'temp/d1_output.txt' using 1:2 with lines" > output/d1_graph.png


# Process additional options (like -d1, -d2, etc.)
shift # Skip the first argument (CSV file)
while (( "$#" )); do
    case "$1" in
        -d1)
            awk -F, '{print $6}' "$csv_file" | sort | uniq -c | sort -nr | head -10 > temp/d1_output.txt
            # Use GnuPlot to create a horizontal histogram from temp/d1_output.txt
            ;;
        -d2)
            awk -F, '{distance[$6]+=$5} END {for (driver in distance) print driver, distance[driver]}' "$csv_file" | sort -k2 -nr | head -10 > temp/d2_output.txt
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


