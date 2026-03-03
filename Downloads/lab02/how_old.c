#include <stdio.h>

int main(int argc, char *argv[])
{
    int current_year = 2024;
    int birth_year;
    int had_birthday;           /* used as boolean */

    /* TODO: ask what year the user was born in */
	printf("What year were you born?");
	scanf("%d", &birth_year);
    /* TODO: ask whether the user has had their birthday yet this year */
	printf("Has your birthday happened yet this year? (1 for yes, 0 for no): ");
	scanf("%d", &had_birthday);
    /* TODO: compute and display the user's age */
	int age = current_year - birth_year;
	if (had_birthday == 0) {
	age = age - 1;
}
	printf("You are %d years old.\n", age);

    return 0;
}
