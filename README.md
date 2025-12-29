# FDF

*This project has been created as part of the 42 curriculum.*

## Description

**FDF** (Fil De Fer, or "wireframe" in French) is a graphics project in the 42 curriculum that introduces students to 3D graphics programming. The project involves creating a simplified 3D representation of a landscape by connecting points with lines to form a wireframe model.

The program reads a map file containing height values and displays it as an isometric projection, allowing users to visualize terrain in 3D. This project serves as an introduction to the MiniLibX graphics library and fundamental concepts in computer graphics.

### Key Features

- Isometric projection of 3D wireframe models
- Map parsing from text files containing height coordinates
- Line drawing using DDA (Digital Differential Analyzer) algorithm
- Color gradient visualization based on height
- Real-time rendering using MiniLibX
- Fully compliant with 42's norminette coding standards

## Instructions

### Prerequisites

- C compiler (cc)
- Make
- A Unix-based operating system

### Installation

Clone the repository:

```bash
git clone https://github.com/caburges/FDF.git
cd FDF
```

### Compilation

To compile the project, run:

```bash
make
```

This will generate an `fdf` executable.

### Usage

Run the program with a map file:

```bash
./fdf maps/42.fdf
```

### Controls

- **ESC** - Exit the program
- **Close button** - Exit the program

### Available Make Rules

- `make` or `make all` - Compiles the project
- `make clean` - Removes object files
- `make fclean` - Removes object files and the executable
- `make re` - Recompiles the entire project

## Project Structure

### Source Files

- **main.c** - Entry point and program initialization
- **initialisation.c** - Map and program initialization
- **init_utils.c** - Utility functions for initialization
- **draw.c** - Drawing functions and rendering logic
- **colour.c** - Color calculation and gradient functions
- **maths.c** - Mathematical transformations and projections
- **maths_utils.c** - Additional mathematical utilities

## Technical Details

### Projection

The project uses isometric projection to transform 3D coordinates into 2D screen coordinates:
- X' = (x - y) * cos(angle)
- Y' = (x + y) * sin(angle) - z

### Line Drawing

Lines are drawn using the DDA (Digital Differential Analyzer) algorithm, which uses floating-point arithmetic to incrementally plot pixels between two points.

### Color Gradients

Colors transition smoothly between points based on their height values, creating a visual depth effect.
