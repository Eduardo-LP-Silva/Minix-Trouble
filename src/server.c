#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <minix/driver.h>
#include <machine/int86.h>

#include "server.h"
#include "Bitmap.h"
#include "time.h"
#include "MACROS.h"

Server* new_server(short x_pos, short y_pos) {

  Server *s = malloc(sizeof(Server));

  s->x_coord = x_pos;
  s->y_coord = y_pos;
  s->width = SERVER_WIDTH;
  s->height = SERVER_HEIGHT;
  s->broken_flag = 0;

  return s;

}

void delete_server(Server* s) {

  free(s);
}

void create_serverArray (Server *server_array[]) {

  server_array[0] = new_server(SERVER1_X, SERVER1_Y);
  server_array[1] = new_server(SERVER2_X, SERVER2_Y);
  server_array[2] = new_server(SERVER3_X, SERVER3_Y);
  server_array[3] = new_server(SERVER4_X, SERVER4_Y);

}

int break_server(Server *server_array[], int n_servers)
{
	long server_n = random_at_most(N_SERVERS);
	Bitmap *broken_server = loadBitmap("/home/lcom/svn/proj/Bitmaps/broken_server.bmp");
  int index = 0; //this variable with save the index of the last good_server, if there is only 1 good server left

	while(1) {

		if(server_array[server_n]->broken_flag == 0){

			drawBitmap(broken_server, server_array[server_n]->x_coord, server_array[server_n]->y_coord, ALIGN_LEFT);
			server_array[server_n]->broken_flag = 1;
      return 0;
		}

  		else if(check_nGoodServers(server_array, n_servers, &index) == 1) {         //if there is only 1 good server, then it will be broke and GAME OVER

      drawBitmap(broken_server, server_array[index]->x_coord, server_array[index]->y_coord, ALIGN_LEFT);
		  return 1;
		}

		else if(server_array[server_n]->broken_flag == 1){

      if(server_n == 3)
        server_n = 0;

      else{
      server_n++;
    }
		}

	}

}

//Checks if there is more than 1 good server. return 0 if there is more than 1 good server, and 1 if not
int check_nGoodServers(Server *server_array[], int n_servers, int *index) {

	int temp = 0;
	int i;

	for(i = 0; i < 4; i++) {

		if(server_array[i]->broken_flag == 0){

			if(temp == 1)
				return 0;

      *index = i;
			temp = 1;
		}

	}

	return 1;
}

long random_at_most(unsigned long max)
{
	srand(time(NULL));

  return rand() % max;
}

int fix_server (Server* server_array[], int n_servers, int serverID, int *score) {

  if(serverID + 1> n_servers)
    return -1;

  if(server_array[serverID]->broken_flag == 1)
  {
	  *score += 20;
	  server_array[serverID]->broken_flag = 0;
  }


  return 0;

}
