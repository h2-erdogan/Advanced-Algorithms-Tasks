# Advanced Algorithms Coursework

## Overview

This project contains implementations for several advanced algorithm tasks, completed as part of the coursework.  
The tasks cover data analysis, algorithm optimization, graph theory, and parallel processing applied to real datasets and problem domains.


## Task Descriptions

### Task 1.1 - Data Analysis on Student Records
In this task, we analyzed university student data using CSV files containing module details and grades.  
We performed data cleaning, aggregation, and statistical analysis to understand student performance trends.

### Task 1.2 - Password Generation and Security Analysis
This task involved generating a list of passwords and analyzing their strength based on criteria like length, character variety, and entropy.  
The program also filtered out weak passwords and saved secure ones.

### Task 1.3 - Graph Algorithms on UK Railway Network
We implemented graph algorithms to solve routing problems on the UK railway map dataset.  
This included finding shortest paths and optimizing routes using algorithms such as Dijkstra and Minimum Spanning Tree.

### Task 1.4 - Parallel Face Recognition
This task focused on speeding up face recognition by using parallel processing techniques.  
The program processed a large set of images to detect and recognize faces efficiently, leveraging multiprocessing.

---

## Project Structure

```
├── task1.1                  # Task 1.1: Data analysis with CSV datasets  
│   ├── data                 # Input CSV files  
│   │   ├── cs modules.csv  
│   │   ├── final_degree_results.csv  
│   │   └── task1_1_marks.csv  
│   └── task1.1.py           # Main script for Task 1.1  
├── task1.2                  # Task 1.2: Password generation and analysis  
│   ├── generated_passwords.txt  
│   └── task1.2.py  
├── task1.3                  # Task 1.3: Graph problem with UK Railway Map data  
│   ├── task1.3.py  
│   ├── task1_3_UK_Railway_Map.pdf  
│   └── task1_3_data.csv  
├── task1.4                  # Task 1.4: Parallel face recognition algorithm  
│   ├── imageset             # Image dataset for face recognition  
│   ├── known_man.jpg        # Reference image for recognition  
│   └── task1_4_parallel.py  # Parallel processing script  
├── task2_1_report.docx      # Coursework report document  
└── task2_2_demo.mp4         # Demo video of the project  
```

---

## Features

- **Task 1.1:** Data analysis on university student results and modules using CSV files.  
- **Task 1.2:** Generated and analyzed passwords for security criteria.  
- **Task 1.3:** Graph algorithms applied on UK Railway Map for route optimization.  
- **Task 1.4:** Implemented a parallelized face recognition algorithm with a dataset of images.  

---

## Technologies Used

- Python 3.8+  
- Libraries: pandas, numpy, networkx, multiprocessing, OpenCV  
- Data formats: CSV, JPG images  
- Tools: Jupyter Notebook (if used), VSCode  

---

## How to Run

### Prerequisites

- Python 3.8 or higher installed  
- Install required packages:  

```bash
pip install pandas numpy networkx opencv-python
```

### Running Each Task

- **Task 1.1:**  
Navigate to `task1.1` folder and run:  
```bash
python task1.1.py
```

- **Task 1.2:**  
Navigate to `task1.2` folder and run:  
```bash
python task1.2.py
```

- **Task 1.3:**  
Navigate to `task1.3` folder and run:  
```bash
python task1.3.py
```

- **Task 1.4:**  
Navigate to `task1.4` folder and run:  
```bash
python task1_4_parallel.py
```

---

## Notes

- Make sure data files are in their correct folders as per the structure above.  
- For Task 1.4, ensure that the `imageset` folder contains all images for the face recognition to work properly.  


---
