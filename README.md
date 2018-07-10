# Refraction IDE

*Making things look different*

## General description
Refraction is an integrated development environment (IDE), designed to work with black box testing. It allows to edit, compile, run and then compare the result of your program to input / expected output files.

## Why is this needed?
While working with test cases, automatic judges (online judges) are usually very cruel, and even a small diference such as a whitespace or a colon makes a test case fail. Using Refraction, you can visually identify **where** the error is located and fix it quickly.

When you run your code using Refraction IDE, a list is shown with all of the test cases, using green to show the ones that are correct, and red for the wrong ones. When you click on a test case, it is displayed below, using different colors to highlight the diferences with the expected output.

## How to use it
In order to use Refraction IDE, open the editor, load your test cases, write your code and run. That's when the magic happens. On the bottom of your screen, the test cases will apear, using beautiful colors to show the differences between your output, and the expected result.

## Special props
* The text editor uses colors to highlight reserved words as in any code editor.
* Visual comparison of test cases and code output.
* In-site compilation and program running.

## Requirements
* A C/C++ compilator installed.
* The QT library installed.
* A folder built by the user, that contains the "Solution.(c/cpp)", and the test cases using the format `input#.*` and `output#.*`.
* This software is designed to work on Linux devices.

## About this project
This software was developed as a final project for the Programming 2 class, on the University of Costa Rica, by the students: Bryan Ulate, Cristian Rodriguez and Diego Orozco, under the guide of proffesor Jeisson Hidalgo.
