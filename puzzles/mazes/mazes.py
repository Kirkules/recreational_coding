from random import randint, shuffle
from unionfind import unionfind


class NumberMaze:
    """
    A maze consisting of a bounded section of a (usually rectangular) grid of locations containing numbers.
    The goal is to start at number 1, usually on the border of the grid section, and proceed to a goal number,
    also usually on the border of the section.
    """

    def reset_edges(self, width=25, height=25):
        # Vertical edges:   v_edge i, j is between entry i, j and i+1, j
        #                   v_edge[i][j] = 1 if (i, j) -> (i+1, j)
        #                                 -1 if (i, j) <- (i+1, j)
        #                                  0 if no edge
        self.v_edge = [[0 for _ in range(width-1)] for _ in range(height-1)]

        # Horizontal edges: h_edge i, j is between entry i, j and i, j+1
        #                   h_edge[i][j] = 1 if (i, j) -> (i, j+1)
        #                                 -1 if (i, j) <- (i, j+1)
        #                                  0 if no edge
        self.h_edge = [[0 for _ in range(width-1)] for _ in range(height-1)]

    def reset_entries(self, width=25, height=25):
        self.entry = [[None for _ in range(width)] for _ in range(height)]

    def __init__(self):
        self.entry = None
        self.v_edge = None
        self.h_edge = None

    def is_edge(self, start, end):
        # Vertical edges
        if (start[1] == end[1] and abs(start[1]-end[1]) == 1):
            return self.h_edge[start[0]][min(start[1], end[1])]

        # Horizontal edges
        if (start[0] == end[0] and abs(start[1]-end[1]) == 1):
            return self.h_edge[start[0]][min(start[1], end[1])]

    def is_adjacent(self, a, b):
        # a and b are adjacent if they're distinct and differ in either row or column by 1, but not both
        return a != b and (abs(a[0] - b[0]) == 1) != (abs(a[1] - b[1]) == 1)

    def generate_rectangular(self, path_length=100, width=25, height=25):
        start = [randint(0, height), 0]
        end = [0, randint(0, width)]
        reset_entries()
        reset_edges()

        available_edges = [(i, j) if i != end[0] and j != end[1]
                              for i in range(height-1)
                              for j in range(width-1)

        shuffle(available_edges)

        uf = unionfind(width*height)

        # Keep track of connected components of the maze, and make sure the directoion of edges
        # points away from the start.

        # Choose a random edge and add it if one of its vertices is part of the tree already,
        # with direction leading away from the tree. Just don't admit an edge to the end location
        # until the rest of the edges are connected.
        while (len(available_edges) > 0):
            next_edge = randint(len(available_edges))
