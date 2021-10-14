/*
	Curso de Ciencia de la Computación I - CCOMP2 - 1
	SNAKE PRIMERA PARTE

	Alumnos:
	- Albert Yerem Cáceres Marca
	- Jhon Berly Taipe Alccaccahua
	- Brian Jesse Bermudez Navarro
*/

#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<conio.h>

#define UP 72
#define DOWN 80
#define RIGTH 77
#define LEFT 75

int veloci=100000000;
int comida2_x=-1,comida2_y=-1;
int ni=0,posx=5,posy=5,comida2=0;

int ncuerpo=1;
int cuerpo[100][2];

int vida[100][2];
int vidas=3;

int puntuacion = 0;

bool turno= true;

int n=0+rand() % (10),m=1+rand() % (10),min=1;


// relleno_de_la_matriz dibuja la imprecion por pantalla
void relleno_de_la_matriz(char matriz[10][10]){
	int man=0;
	std::cout << "============" << std::endl;
	for(int t=0; t<10; ++t){
		std::cout << "|";
		for (int j=0;j<10;++j){
			
			for (int h=0; h<ncuerpo;++h){
				if (t==cuerpo[h][0] && j==cuerpo[h][1] && h==ncuerpo-1){
					std::cout<<"X";
					man=1;
				} else if(t==cuerpo[h][0] && j==cuerpo[h][1]){
					std::cout<<"@";
					man=1;
                }
            }
			if (man==1){
				man=0;
            } else if(n==t && m==j){
				std::cout<<"o";
            } else if (comida2_x==t && comida2_y==j){
				std::cout<<"0";
			}
			else{
                std::cout<<" ";
            }
		}
		std::cout << "|";
		std::cout<<"\n";
    }
	std::cout << "============" << std::endl;
}

// la funcion mover recive teclas por el usuario y las reserva la variable ni que sera usada mas adelante
void mover(){
	if (kbhit()){
		char teclas=getch();
		switch(teclas){
			case UP:
				ni=1;
				break;
			case DOWN:
				ni=2;
				break;
			case RIGTH:
				ni=3;
				break;
			case LEFT:
				ni=4;
				break;
        }
    }
}


// formas de perder ejecuta el poder traspasar paredes y retrocede una posicion cuando
// choca con su cuerpo y se detiende.
void formas_de_perder(){
	if (cuerpo[ncuerpo-1][0]>=10){
		cuerpo[ncuerpo-1][0]=0;
		veloci=veloci-7000000;
	}else if (cuerpo[ncuerpo-1][1]>=10) {
		cuerpo[ncuerpo-1][1]=0;
		veloci=veloci-7000000;
	} else if  (cuerpo[ncuerpo-1][0]<=-1) {
		cuerpo[ncuerpo-1][0]=9;
		veloci=veloci-7000000;
	}else if (cuerpo[ncuerpo-1][1]<=-1) {
		cuerpo[ncuerpo-1][1]=9;	
		veloci=veloci-7000000;
	}
	for(int j=ncuerpo-2;j>=0;--j){
		if((cuerpo[j][0]==cuerpo[ncuerpo-1][0])&&(cuerpo[j][1]==cuerpo[ncuerpo-1][1])){
			for(int r=0 ; r<ncuerpo;++r){
				cuerpo[r][0]=vida[r][0];
				cuerpo[r][1]=vida[r][1];
				ni=0;
			}
			vidas=vidas-1;
        }
    }
}


// La siguiente funcion hace posible el avance
void movimiento_gusano(int direccion){
	mover();
	int a[2],b[2];
	for(int i=0;i<ncuerpo;++i ){
		vida[i][0]=cuerpo[i][0];
		vida[i][1]=cuerpo[i][1];
    }
	
	for(int j=ncuerpo-1;j>=0;j=j-1){
		if(ni>0){
			if (j==(ncuerpo-1)){
				a[0]=cuerpo[j][0];
				a[1]=cuerpo[j][1];

				if (direccion==1){
					cuerpo[j][0]=(cuerpo[j][0])-1;
					formas_de_perder();
                } else if(direccion==2){
					cuerpo[j][0]=(cuerpo[j][0])+1;
					formas_de_perder();
                } else if (direccion==3){
					cuerpo[j][1]=(cuerpo[j][1])+1;
					formas_de_perder();
                } else if (direccion==4){
					cuerpo[j][1]=(cuerpo[j][1])-1;
					formas_de_perder();
                }
            } else{
				b[0]=cuerpo[j][0],b[1]=cuerpo[j][1];
				cuerpo[j][0]=a[0],cuerpo[j][1]=a[1];
				a[0]=b[0],a[1]=b[1];
            }
        }
    }
}


// si la posicion de la cabeza es igual ala pos de la comina la variable ncuerpo aumenta y puntacion tambien
void comer(){
	if (cuerpo[ncuerpo-1][0]==n && cuerpo[ncuerpo-1][1]==m){
		mover();
		if (ni==1){
			cuerpo[ncuerpo][0]=(cuerpo[ncuerpo-1][0])-1;
			cuerpo[ncuerpo][1]=cuerpo[ncuerpo-1][1];
		} else if (ni==2){
			cuerpo[ncuerpo][0]=(cuerpo[ncuerpo-1][0])+1;
			cuerpo[ncuerpo][1]=cuerpo[ncuerpo-1][1];
		} else if (ni==3){
			cuerpo[ncuerpo][1]=(cuerpo[ncuerpo-1][1])+1;
			cuerpo[ncuerpo][0]=cuerpo[ncuerpo-1][0];
		} else if (ni==4){
			cuerpo[ncuerpo][1]=(cuerpo[ncuerpo-1][1])-1;
			cuerpo[ncuerpo][0]=cuerpo[ncuerpo-1][0];
		}
		formas_de_perder();
		ncuerpo=ncuerpo+1;
		puntuacion += 10;
		n=0 + rand() % (10),m=0 + rand() % (10);
		min=0;
	}
	if (cuerpo[ncuerpo-1][0]==comida2_x && cuerpo[ncuerpo-1][1]==comida2_y ){
		veloci=100000000;
		comida2=0;
	}
}


int main(){
	char plano[10][10];
	// donde inicia
	cuerpo[0][0]=5,cuerpo[0][1]=5;


	// deseno menu inicio
	std::cout << "\n\n************************************************\n*********************SNAKE**********************\n************************************************\n" << std::endl;
	std::cout << "intrucciones: " << std::endl;
	std::cout << "\t+\tPodras traspasar paredes pero\n\t\tse te aumentara la velocidad\n\t\teste efecto podra revertirse\n\t\tcomiento un vonus que aparacera\n\t\tcada cierto tiempo." << std::endl;
	std::cout << "\n\t+\tTIENES 3 VIDAS\n" << std::endl;
	std::string quieres_jugar;
	std::cout << "Quieres empezar (S/N): ";
	std::cin >> quieres_jugar ;

	// bucle  de condicion
	while (true)
	{
		if (quieres_jugar == "S"){
			cuerpo[0][0]=5,cuerpo[0][1]=5;
			veloci=100000000;
			comida2_x=-1,comida2_y=-1;
			ni=0,posx=5,posy=5,comida2=0;

			ncuerpo=1;
			vidas=3;

			puntuacion = 0;

			turno= true;

			n=0+rand() % (10),m=1+rand() % (10),min=1;
			
			// bucle del juego principal
			while(turno){
				for (int w=0;w<veloci;++w){}	
				mover();
				relleno_de_la_matriz(plano);
				mover();
				movimiento_gusano(ni);
				comer();
				if (min==20){
					srand(time(NULL));
					n=0 + rand() % (10),m=0 + rand() % (10);
					min=1;
				}
				if (comida2<100 ){
					comida2_x=-1,comida2_y=-1;	
				}
				else if (comida2==115){
					comida2_x=-1,comida2_y=-1;
					comida2=0;	
				}
				else if (comida2==100){
					srand(time(NULL));
					comida2_x=0 + rand() % (10),comida2_y=0 + rand() % (10);	
				}
				min=min+1;
				comida2=comida2+1;
				if (vidas==0){
					std::cout<<"perdiste";
					break;
				}
				std::cout << "Puntuacion: " << puntuacion << std::endl;
				std::cout << "VIDAS: " << vidas << std::endl;
				//printf("\033[H\033[J");
				//system("cls");
			}
			// deseno parte final
			std::cout << "\n****************************************\n***************GAME OVER****************\n****************************************" << std::endl;
			std::cout << "PUNTUACION: " << puntuacion << std::endl<< std::endl<< std::endl;
			// pregunta si el usuario quiere segir jungando o rendirse
			std::cout << "Quieres volver a intentar(S/N): ";
			std::cin >> quieres_jugar;
		} else {
			break;
		}
	}
	return 0;
}
