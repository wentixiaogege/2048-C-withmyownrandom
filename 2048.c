#include <climits>
#include <cstdio>
#include <cstring>
#include <stack>
#include <string>
#include <map>
#include <vector>
#include <cmath>


using namespace std;

const int MAXX = 10;

int box[MAXX][MAXX];

void moveLeft(int n, bool &ret){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			int k;
			for (k = j - 1; k >= 0; --k){
				if (box[i][k] != -1){
					break;
				}
			}
			box[i][k + 1] = box[i][j];

			if ((k + 1) != j){
				box[i][j] = -1;
				ret = true;
			}
		}
	}
}

void mergeLeft(int n, bool &ret){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n - 1; ++j){
			if (box[i][j] == -1)continue;

			if (box[i][j] == box[i][j + 1]){
				box[i][j] *= 2;
				box[i][j + 1] = -1;
				ret = true;
				++j;
			}
		}
	}
}

bool left(int n){
	bool ret = false;
	moveLeft(n, ret);
	mergeLeft(n, ret);
	moveLeft(n, ret);
	return ret;
}

void moveRight(int n, bool &ret){
	for (int i = 0; i < n; ++i){
		for (int j = n - 1; j >= 0; --j){
			if (box[i][j] == -1)continue;

			int k;
			for (k = j + 1; k < n; ++k){
				if (box[i][k] != -1){
					break;
				}
			}

			box[i][k - 1] = box[i][j];
			if ((k - 1) != j){
				box[i][j] = -1;
				ret = true;
			}
		}
	}
}

void mergeRight(int n, bool &ret){
	for (int i = 0; i < n; ++i){
		for (int j = n - 1; j >0; --j){
			if (box[i][j] == -1)continue;

			if (box[i][j] == box[i][j - 1]){
				box[i][j] *= 2;
				box[i][j - 1] = -1;
				ret = true;
				--j;
			}
		}
	}
}

bool right(int n){
	bool ret = false;
	moveRight(n, ret);
	mergeRight(n, ret);
	moveRight(n, ret);
	return ret;
}

void moveUp(int n, bool &ret){
	for (int j = 0; j < n; ++j){
		for (int i = 0; i < n; ++i){
			int k;
			for (k = i - 1; k >= 0; --k){
				if (box[k][j] != -1){
					break;
				}
			}
			box[k + 1][j] = box[i][j];

			if ((k + 1) != i){
				box[i][j] = -1;
				ret = true;
			}
		}
	}
}

void mergeUp(int n, bool &ret){
	for (int j = 0; j < n; ++j){
		for (int i = 0; i < n - 1; ++i){
			if (box[i][j] == -1)continue;

			if (box[i][j] == box[i + 1][j]){
				box[i][j] *= 2;
				box[i + 1][j] = -1;
				ret = true;
				++i;
			}
		}
	}
}

bool up(int n){
	bool ret = false;
	moveUp(n, ret);
	mergeUp(n, ret);
	moveUp(n, ret);
	return ret;
}

void moveDown(int n, bool &ret){
	for (int j = 0; j < n; ++j){
		for (int i = n - 1; i >= 0; --i){
			if (box[i][j] == -1)continue;

			int k;
			for (k = i + 1; k < n; ++k){
				if (box[k][j] != -1)break;
			}

			box[k - 1][j] = box[i][j];

			if ((k - 1) != i){
				box[i][j] = -1;
				ret = true;
			}
		}
	}
}

void mergeDown(int n, bool &ret){
	for (int j = 0; j < n; ++j){
		for (int i = n - 1; i > 0; --i){
			if (box[i][j] == -1)continue;

			if (box[i][j] == box[i - 1][j]){
				box[i][j] *= 2;
				box[i - 1][j] = -1;
				ret = true;
				--i;
			}
		}
	}
}

bool down(int n){
	bool ret = false;
	moveDown(n, ret);
	mergeDown(n, ret);
	moveDown(n, ret);
	return ret;
}

void line(int n){
	for (int i = 0; i < n; ++i){
		printf("--------");
	}
	printf("-");
	printf("\n");
}

void print(int n){
	for (int i = 0; i < n; ++i){
		line(n);
		for (int j = 0; j < n; ++j){
			printf("|");
			if (box[i][j] == -1){
				printf("\t");
				continue;
			}

			printf("%2d\t", box[i][j]);
		}
		printf("|");
		printf("\n");
	}
	line(n);
}

bool isFull(int n){
	bool mark = true;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if (box[i][j] == -1){
				mark = false;
				return mark;
			}
		}
	}
	return mark;
}

bool isOver(int n){
	if (!isFull(n)){
		return false;
	}
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if (box[i][j] == box[i][j + 1] || box[i][j] == box[i + 1][j]){
				return false;
			}
		}
	}
	return true;
}

void fillBox(int n){
	int i, j, num;

	if (isFull(n)){
		return;
	}

	while (true){
		i = rand() % n;
		j = rand() % n;
		num = rand() % 2 == 0 ? 2 : 4;

		if (box[i][j] == -1){
			box[i][j] = num;
			break;
		}
	}
}

int main(){
	//freopen("in.txt", "r", stdin);
	memset(box, -1, sizeof(box));

	int n;
	bool mark;
	scanf("%d%*c", &n);

	fillBox(n);
	fillBox(n);
	print(n);

	while (true){
		char ch;
		scanf("%c%*c", &ch);
		if (ch == 'a'){
			mark = left(n);
		}
		else if (ch == 'd'){
			mark = right(n);
		}
		else if (ch == 'w'){
			mark = up(n);
		}
		else if (ch == 's'){
			mark = down(n);
		}
		else{
			continue;
		}
		system("cls");
		printf("Move:\n");
		print(n);
		if (!mark){
			continue;
		}
		fillBox(n);
		printf("Fill:\n");
		print(n);

		if (isOver(n)){
			printf("\n\nGame Over!\n\n");
			break;
		}
	}
	
	
	return 0;
}
