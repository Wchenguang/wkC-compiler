int number = 123;
int another_number = 456;
number = anather_number;

string str1 = "woshiwcg";
string str2 = "niupiboy";
str1 = str2;

char a = 'v';
char b = 'b';
a = b;

int hello(int a, int b){
	if(a == b){
		return 1;
	}else if(a < b){
		return 2;
	}else if(a > b){
		return 3;
	}
}

int main(){
	printf("%s\n", "hello world");
	return 0;
}
