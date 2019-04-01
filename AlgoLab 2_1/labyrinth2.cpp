#include <iostream>
#include <fstream>
#include <forward_list>
#include <queue>
#include <string>

struct vertex {
    bool visited = false;
    bool finish = false;

    int x, y;
    std::string way = "";

    int dist = -1;
};

vertex * dfs(vertex ** map, int x, int y, int n, int m);

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int n, m;
    input >> n >> m;

    vertex ** map = new vertex * [m];
    for (int k = 0; k < m; k++)
        map[k] = new vertex[n];

    char ch;
    int x, y; // start coords
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            input >> ch;

            map[i][j].x = i;
            map[i][j].y = j;

            if (ch == '#')
                map[i][j].visited = true;
            else if (ch == 'S') {
                x = i;
                y = j;
            }
            else if (ch == 'T')
                map[i][j].finish = true;
        }
    }

    vertex * vert = dfs(map, x, y, n, m);
    if (vert != nullptr && vert->finish) {
        output << vert->dist << std::endl;
        output << vert->way;
    } else output << -1;

    input.close();
    output.close();

    return 0;
}

vertex * dfs(vertex ** map, int x, int y, int n, int m) {
    vertex *start = &map[x][y];

    start->dist = 0;
    start->visited = true;
    start->way = "";

    return dfs_visit(start, map);
}

    while(!queue.empty()) {
        vert = queue.front();
        queue.pop();

        if (vert->finish) {
            finish_found = true;
            break;
        }

        if (vert->x > 0 && !map[vert->x - 1][vert->y].visited) {
            queue.push(&map[vert->x - 1][vert->y]);
            map[vert->x - 1][vert->y].visited = true;
            map[vert->x - 1][vert->y].dist = vert->dist + 1;
            map[vert->x - 1][vert->y].way = vert->way + "L";
        }
        if (vert->x < (m - 1) && !map[vert->x + 1][vert->y].visited) {
            queue.push(&map[vert->x + 1][vert->y]);
            map[vert->x + 1][vert->y].visited = true;
            map[vert->x + 1][vert->y].dist = vert->dist + 1;
            map[vert->x + 1][vert->y].way = vert->way + "R";
        }
        if (vert->y > 0 && !map[vert->x][vert->y - 1].visited) {
            queue.push(&map[vert->x][vert->y - 1]);
            map[vert->x][vert->y - 1].visited = true;
            map[vert->x][vert->y - 1].dist = vert->dist + 1;
            map[vert->x][vert->y - 1].way = vert->way + "U";
        }
        if (vert->y < (n - 1) && !map[vert->x][vert->y + 1].visited) {
            queue.push(&map[vert->x][vert->y + 1]);
            map[vert->x][vert->y + 1].visited = true;
            map[vert->x][vert->y + 1].dist = vert->dist + 1;
            map[vert->x][vert->y + 1].way = vert->way + "D";
        }

    }

    if (finish_found)
        return vert;
    else return nullptr;

}
vertex * dfs_visit(vertex * vert, vertex ** map) {
    if (vert->x > 0 && !map[vert->x - 1][vert->y].visited) {
        map[vert->x - 1][vert->y].visited = true;
        map[vert->x - 1][vert->y].dist = vert->dist + 1;
        map[vert->x - 1][vert->y].way = vert->way + "L";
    }
    if (vert->x < (m - 1) && !map[vert->x + 1][vert->y].visited) {
        queue.push(&map[vert->x + 1][vert->y]);
        map[vert->x + 1][vert->y].visited = true;
        map[vert->x + 1][vert->y].dist = vert->dist + 1;
        map[vert->x + 1][vert->y].way = vert->way + "R";
    }
    if (vert->y > 0 && !map[vert->x][vert->y - 1].visited) {
        queue.push(&map[vert->x][vert->y - 1]);
        map[vert->x][vert->y - 1].visited = true;
        map[vert->x][vert->y - 1].dist = vert->dist + 1;
        map[vert->x][vert->y - 1].way = vert->way + "U";
    }
    if (vert->y < (n - 1) && !map[vert->x][vert->y + 1].visited) {
        queue.push(&map[vert->x][vert->y + 1]);
        map[vert->x][vert->y + 1].visited = true;
        map[vert->x][vert->y + 1].dist = vert->dist + 1;
        map[vert->x][vert->y + 1].way = vert->way + "D";
    }
}