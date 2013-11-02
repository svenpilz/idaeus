#include <stdio.h>
#include <string.h>

/**
 * Converts GNU Unifont Glyphs (.hex format) for Idaeus.
 * Usage: convert-font < unifont.hex > font.
 * See "http://unifoundry.com/unifont.html".
*/

int main(void) {
	char output[95][16];
	char line[38];
	size_t c;
	size_t i;
	char buf[4];
	
	memset(output, 0, sizeof(output));
	
	for (c = 0; c < 95; c++) {
		memset(line, 0, sizeof(line));
		memset(buf, 0, 4);
		
		if (fread(line, 38, 1, stdin) != 1) {
			break;
		}
		
		line[37] = 0;
		/*fprintf(stderr, "%s\n     ", line);*/
		
		for (i = 0; i < 16; i++) {
			buf[0] = line[5 + i*2];
			buf[2] = line[5 + i*2 + 1];
			
			output[c][i] = (strtoul(&buf[0], NULL, 16) << 4) | strtoul(&buf[2], NULL, 16);
			/*fprintf(stderr, "%.2hhx", output[c][i]);*/
		}
		
		/*fprintf(stderr, "\n\n");*/
	}
	
	fwrite(output, sizeof(output), 1, stdout);
	return 0;
}
