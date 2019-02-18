# Polygon-Clipping
Clips any polygon using specific algorithms + additional features. Multiple helper functions were implemented for this to work. The concept of ``vectors`` and ``push_back`` in C++ were used in this program.

# Algorithms

The most important function is the listPolygon() function, which stores and organizes a set of points provided by the user using push_back, which appends new data to the end of existing data. I think of it like a stack.

```C++
std::vector<Point> listPolygon() {
	std::vector<Point> pointList;
	int n, x, y;
	printf("# of vertices: >> ");
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("Enter point in a clockwise form: >> ");
		scanf("%d %d", &x, &y);
		pointList.push_back(Point{x, y});
	}
	return pointList;
}
```

The ``movePolygon()`` function simply translates a polygon's set of vertices by a certain point.
# Bresenham Line Algorithm
The Bresenham Line Algorithm was also included in this program. 
Source: https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
The cited code was edited to work with the program.
# Other
There are additional, unmentioned functions in this README. Due to incompletion, the remaining clipping algorithms were not implemented. If there way anything I could ask for in order to completely understand this material, it would be for some time allocated explaining the solution during or after the tutorials/class.
