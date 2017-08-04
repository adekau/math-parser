#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() {
	char pattern[50] = "[0-9]+";
	size_t d = 2;
	regmatch_t pmatch[2];
	printf("%s\n", pattern);
	int ereg;
	regex_t regex;
	ereg = regcomp(&regex, pattern, REG_EXTENDED);
	if (ereg) {
		fprintf(stderr, "Could not compile regex %s\n", pattern);
		return 0;
	}

	ereg = regexec(&regex, "123 456", d, pmatch, 0);
	if (!ereg) {
		puts("Match!");
	} else if (ereg == REG_NOMATCH) {
		puts("no match!");
	} else {
		puts ("error!");
	}

}
