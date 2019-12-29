//Connection handling based upon https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>


#define PORT 1717

int day;

int line_count(const char* file){
    int count=0;
    char currentChar;
    FILE* fd=fopen(file,"r");
    if(fd==NULL){
        perror("Error opening the quotes file");
        exit(EXIT_FAILURE);
    }
    while(true){
        currentChar=fgetc(fd);
        switch (currentChar){
            case '\n':{
                count++;
                break;
            }
            case EOF:{
                fclose(fd);
                return count;
            }

        }
    }
}

char* read_random_quote_from_file(const char* filePath){
   int numOfQuotes=line_count(filePath);
   int lineNumberOfQOTD=rand()%numOfQuotes;
   int lineCounter=0;
   char* lineptr=NULL; //will contain the address of the buffer containing the quote
   size_t n=0; //calling getline with lineptr=NULL and n=0 makes it automatically allocate the right amount of memory
   FILE* fd=fopen(filePath, "r");
    if(fd==NULL){
        perror("Error opening the quotes file");
        exit(EXIT_FAILURE);
    }
   while(lineCounter<lineNumberOfQOTD){ //seek the file until it reaches the line we want to read
       if(fgetc(fd)=='\n') lineCounter++;
   }
    getline(&lineptr, &n, fd);    //stores the line read from fd into a buffer and sets lineptr to the buffer's address
    fclose(fd);
    return lineptr;
}

bool a_day_has_passed() {

}

void signal_handler(int signal) {
    a_day_has_passed();
}

int main(int argc, char const *argv[])
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *QOTD = read_random_quote_from_file("quotes.txt");

	/*to check if a day has passed I create a timer that sends a SIGUSR1 signal every hour. The signal gets hamdled by
	 * the program by calling the a_day_has_passed() function. If a day has passed, the quote gets replaced.
	 */

	//set handler for signal SIGUSR1 (timer elapsed)
	struct sigaction timerElapsedAction;

	sigaction(SIGUSR1, );
	sigevent_t notification={SIGEV_SIGNAL, SIGUSR1};  //check man for sigevent(7)
	//create a timer that sends SIGUSR1 every hour
    timer_t* checkNewDayTimer=(timer_t)malloc(sizeof(timer_t));
	timer_create(CLOCK_REALTIME, &notification, checkNewDayTimer);  //todo: correctly check for errors //check man for timer_create(2)

	//https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program
	time_t time1=time(NULL); //number of second elapsed since epoch
    struct tm tm = *localtime(&time1);
    day=tm.tm_mday; //The day of the month, in the range 1 to 31

	printf("Running as user %s", getlogin());
	printf("\n");

    srand(time1);  //To randomize quotes

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 1717
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 1717
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 100) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	printf("Listening on port %i\n", PORT);

	while(1) {  //connection handler loop
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        send(new_socket, QOTD, strlen(QOTD), 0);
        close(new_socket);
    }
	return 0;
}