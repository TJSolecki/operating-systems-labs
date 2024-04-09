# Name: Thomas Solecki
# Date: 4/2/2024
# Title: Lab1 – Circle area & perimeter calculator
# Description: This program computes the area & perimeter of a circle with a provided radius.
#!/bin/bash

calculate_area() {
    radius=$1
    area=$(echo "scale=2; 3.14159 * $radius * $radius" | bc)
    echo "Area of the circle: $area"
}

calculate_perimeter() {
    radius=$1
    perimeter=$(echo "scale=2; 2 * 3.14159 * $radius" | bc)
    echo "Perimeter of the circle: $perimeter"
}

echo "Please enter the radius of the circle:"
read radius

# Checking that the radius provided is strictly a positive integer
if [[ $radius =~ ^[0-9]*([0-9]+)?$ && $radius > 0 ]]; then
    calculate_area $radius
    calculate_perimeter $radius
else
    echo "ERROR: Enter a positive number for the radius of the circle."
fi

