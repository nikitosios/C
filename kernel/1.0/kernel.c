/* main kernel source file */
void kmain(void)
{
	const char *str = "my first kernel";
	char *vidptr = (char *) 0xb8000; /* video memory begins here */
	unsigned int i, j;
	
	/* this loop clears the screen
	 * there are 25 lines each of 80 columns; each element takes 2 bytes */
	for (j = 0; j < 80 * 25 * 2; j += 2) {
		/* blank character */
		vidptr[j] = ' ';
		/* attribute-byte - light grey on black screen */
		vidptr[j+1] = 0x07;
	}

	/* this loop writes the string to video memory */
	for (j = 0, i = 0; str[j] != '\0'; ++j, i += 2) {
		/* the character's ascii */
		vidptr[i] = str[j];
		/* attribute-byte: give character black bg and light grey fg */
		vidptr[i+1] = 0x07;
	}
	return;
}
