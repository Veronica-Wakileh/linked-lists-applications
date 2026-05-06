# Linked Lists Applications – Palestinian Districts and Towns Population System

## 1. Project Overview

This project is a menu-driven program written in C that manages information about Palestinian districts, their towns, and the population of each town. The program reads the data from an input file, stores it using linked lists, and allows the user to perform several operations such as sorting, inserting, deleting, searching, and calculating populations.

The main goal of this project is to practice working with linked lists, file handling, and sorting algorithms (Radix Sort) as part of the Data Structures and Algorithms course.

## 2. Course Information

- **Course:** Data Structures and Algorithms
- **Course Code:** COMP2421
- **Project:** Linked Lists Applications
- **Language:** C

## 3. Main Idea

The program represents Palestine as a list of districts. Each district has a list of towns, and each town has a population value. To organize this data, two linked lists are used together:

- One linked list for the districts.
- For every district, a separate linked list for its towns.

The user interacts with the program through a menu that offers options to load the data, sort it, modify it, and save the results to an output file.

## 4. Data Structures Used

The program uses **two doubly linked lists**:

- **District list:** A doubly linked list where each node stores the district name, total population, a pointer to the next and previous districts, and a pointer to the town list of that district.
- **Town list:** A doubly linked list where each node stores the town name, population, and pointers to the next and previous towns.

Each district node is connected to its own town list through a pointer, which links the two linked lists together.

Memory for nodes is allocated dynamically using `malloc`, and freed using `free` when nodes are deleted.

## 5. Program Features

The program supports the following operations through its menu:

1. Load the input file `districts.txt` containing districts, towns, and populations.
2. Print the loaded data before sorting (in the original input format).
3. Sort the districts alphabetically using **Radix Sort** on strings.
4. Sort the towns of each district by population in ascending order using **Radix Sort** on integers.
5. Print the sorted districts and their towns.
6. Add a new district to the list and re-sort the districts.
7. Add a new town to a selected district.
8. Delete a town from a specific district.
9. Delete a complete district along with its towns.
10. Calculate the total population of Palestine, and find the towns with the maximum and minimum population.
11. Print each district with its total population.
12. Change the population of a specific town.
13. Save the sorted information into the output file `sorted_districts.txt`.
14. Exit the program.

The program combines the main concepts covered in the course: linked lists, file handling, sorting, insertion, deletion, searching, and population calculations.

## 6. Input File Format

The input file is named `districts.txt` and must be placed in the same folder as the executable.
Each line in the file has the following format:

```
District|Town|Population
```

Example:

```
Ramallah|Birzeit|6500
Ramallah|Beitunia|25000
Nablus|Huwara|6800
Hebron|Yatta|70000
```

- The three fields are separated by the `|` character.
- The population must be an integer value.
- A district name may appear in many lines (one line per town).

## 7. Output File

When the user selects option **13**, the program generates an output file called `sorted_districts.txt` containing the sorted districts and their towns, along with the total population of each district.

Example of the output format:

```
Hebron, Population=95000
Yatta,70000
Dura,25000

Nablus, Population=6800
Huwara,6800
```

## 8. Example Menu

When the program runs, the following menu is displayed:

```
Menu of my application
Please select an operation
1-load the input file(Palestinian districts and their town with population)
2-Print the loaded information before sorting(as in the input file format)
3-Sort the districts alphabetically using Radix sort
4-Sort the towns for each district based on population in ascending order.
5-Print the sorted information
6-Add a new district to the list of sorted districts (and sort the list)
7-Add a new town to a certain district
8-Delete a town from a specific district
9-Delete a complete district
10-Calculate the population of Palestine, the max and min town population
11-Print the districts and their total population
12-Change the population of a town
13-Save to output file
14-Exit
```

The user enters the number of the operation, and the program performs it. The menu keeps appearing until the user chooses option 14 to exit.

## 9. Notes about the Implementation

- The district list uses a **head node** with no data, which makes insertion and deletion operations easier.
- Each district node holds a pointer to its own town list, which connects the two linked lists.
- **Radix Sort** is used for both sorting tasks:
  - For districts, it sorts character by character from the last character to the first. Spaces are added temporarily to make all district names the same length, and they are removed again after sorting.
  - For towns, it sorts digit by digit based on the population value.
- Some operations (such as sorting, printing, and saving) automatically load the file if the list is still empty.
- The program uses `strcasecmp` to make name comparisons case-insensitive when searching for districts or towns.
- Input strings are read using `gets` so that names containing spaces (for example, "Beit Jala") can be entered correctly.
- Dynamic memory is freed when towns or districts are deleted to avoid memory leaks.


