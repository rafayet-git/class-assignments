#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

struct pop_entry {
	int year;
	int population;
	char boro[15];
};

int readcsv(){
	int csvfile = open("nyc_pop.csv", O_RDONLY);
	if (csvfile == -1){ 
		printf("%s: nyc_pop.csv\n", strerror(errno));
		exit(errno);
	} 
	char *boros[6];
	remove("nyc_pop.dat");
	int datafile = open("nyc_pop.dat", O_WRONLY | O_CREAT, 0777);
	struct stat csvstat;
	stat("nyc_pop.csv", &csvstat);
	char csvstr[csvstat.st_size];
	read(csvfile, csvstr, csvstat.st_size);
	char *csvstri = csvstr;
	char *cline = strtok_r(csvstri, "\n", &csvstri);
	char *newst = strdup(cline);
	char *newstk = strtok_r(newst, ",", &newst);
	int i=0;
	while(newstk){
		boros[i] = strdup( newstk);
		i++;	
		newstk = strtok_r(newst, ",", &newst);
	}
	
	
	cline = strtok_r(csvstri, "\n", &csvstri);
	struct pop_entry newstru;
	int curyear;
	while(cline){
		i = 1;
		newst = strdup(cline);
		newstk = strtok_r(newst, ",", &newst);
		curyear = atoi(newstk);
		newstk = strtok_r(newst, ",", &newst);
		while (newstk){
			newstru.year = curyear;
			newstru.population = atoi(newstk);
			strcpy(newstru.boro, boros[i]);
			i++;
			write(datafile, &newstru, sizeof(struct pop_entry));
			newstk = strtok_r(newst, ",", &newst);
		}
		cline = strtok_r(csvstri, "\n", &csvstri);
	}

	close(csvfile);
	close(datafile);
	printf("wrote %d bytes to nyc_pop.dat\n", csvstat.st_size);
	return 0;
}

int readata(){
	int dataa = open("nyc_pop.dat", O_RDONLY);
	if (dataa == -1){ 
		printf("%s: nyc_pop.dat\n", strerror(errno));
		exit(errno);
	}
	struct stat datst;
	stat("nyc_pop.dat", &datst);
	int totalstructs = (datst.st_size / sizeof(struct pop_entry));
	int i = 1;
	struct pop_entry cur;
	while(i <= totalstructs){
		read(dataa, &cur, sizeof(struct pop_entry));
		printf("%d: year: %d\tboro: %s\tpop:%d\n", i, cur.year, cur.boro, cur.population);
		i++;
	}
	close(dataa);
	return 0;
}

int addata(){
	int dataa = open("nyc_pop.dat", O_WRONLY | O_APPEND);
	if (dataa == -1){ 
		printf("%s: nyc_pop.dat\n", strerror(errno));
		exit(errno);
	}
	struct pop_entry cur;
	char input[100];
	printf("Enter year boro pop: ");
	scanf("%[^\n]%*c", input);
	char *in1 = input;
	char *ink = strtok_r(in1, " ", &in1);
	cur.year = atoi(ink);
	ink = strtok_r(in1, " ", &in1);
	strcpy(cur.boro, ink);
	ink = strtok_r(in1, " ", &in1);
	cur.population = atoi(ink);
	struct stat sea;
	stat("nyc_pop.dat", &sea);
	int totaldata = (sea.st_size / sizeof( struct pop_entry) ) + 1;
	write(dataa, &cur, sizeof(struct pop_entry));
	printf("Written data as entry %d. \n", totaldata);
	close(dataa);
	return 0;
}

int updata(){
	int dataa = open("nyc_pop.dat", O_RDONLY);
	if (dataa == -1){ 
		printf("%s: nyc_pop.dat\n", strerror(errno));
		exit(errno);
	}
	struct stat datst;
	stat("nyc_pop.dat", &datst);
	int totalstructs = (datst.st_size / sizeof(struct pop_entry));
	struct pop_entry pops[totalstructs];
	int i = 0;
	while (i < totalstructs){
		read(dataa, &(pops[i]), sizeof(struct pop_entry));	
		i++;
	}
	i = 0;
	while (i < totalstructs){
		printf("%d: year: %d\tboro: %s\tpop:%d\n",(i+1), pops[i].year, pops[i].boro, pops[i].population);
		i++;
	}
	int indexnow;
	char input[100];
	printf("Enter year boro pop: ");
	scanf("%[^\n]%*c", input);
	printf("entry to update: ");
	scanf("%d", &indexnow);
	indexnow = indexnow - 1;
	char *in1 = input;
	char *ink = strtok_r(in1, " ", &in1);
	pops[indexnow].year = atoi(ink);
	ink = strtok_r(in1, " ", &in1);
	strcpy(pops[indexnow].boro, ink);
	ink = strtok_r(in1, " ", &in1);
	pops[indexnow].population = atoi(ink);
	close(dataa);
	dataa = open("nyc_pop.dat", O_WRONLY | O_TRUNC);
	i = 0;
	while(i < totalstructs){
		write(dataa, &(pops[i]), sizeof(struct pop_entry));
		i++;
	}

	close(dataa);
	return 0;
}

int main(char argc, char *argv[]){
	if( argc != 2){
		printf("args: -read_csv, -read_data, -add_data, -update_data\n");
		return 0;
	} else if (strcasecmp(argv[1], "-read_csv")==0){
		readcsv();
		return 0;
	} else if (strcasecmp(argv[1], "-read_data")==0){
		readata();
		return 0;
	} else if (strcasecmp(argv[1], "-add_data")==0){
		addata();
		return 0;
	} else if (strcasecmp(argv[1], "-update_data")==0){
		updata();
		return 0;
	} else {
		printf("args: -read_csv, -read_data, -add_data, -update_data\n");
		return 0;
	}

	
}
