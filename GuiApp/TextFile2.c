static void Catch_Bomberman(int enemy_123 ,int x, int y){

	OS_ERR err_os;
	CPU_TS ts;

	int i;
	int j;

	int randomX; 
	int distanceX;

	int randomY; 
	int distanceY;

	BOMBERMAN_POS_X;
	BOMBERMAN_POS_Y;

	while(1){

		randomX = rand()%15;
		randomY = rand()%12;
		OSSemPend(&enemy[enemy_123-1],0,OS_OPT_PEND_BLOCKING, &ts,&err_os);
		distanceX = randomX - ENEMYS_POS[enemy_123 - 1][0];
		distanceY = randomY - ENEMYS_POS[enemy_123 - 1][1];
		OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os); 

		if((distanceX<= 0)&&(distanceY<= 0)){

			if (find_wall_blocks(y,x) == false){
				printf("Distancia1 %i e Distancia2  %i  X %i e Y %i \n ",distanceX,distanceY,x,y);
				Draw_Cover(ENEMYS_POS[enemy_123][0],y);
				OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY, &err_os);
				OSSemPend(&enemy[enemy_123-1],0,OS_OPT_PEND_BLOCKING, &ts,&err_os);
				x--;
				OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);
				ENEMYS_POS[enemy_123-1][0] = x;	
				OSSemPend(&enemy[enemy_123-1],0,OS_OPT_PEND_BLOCKING, &ts,&err_os);
				if (find_wall_blocks(y,x) == false){
					y--;
					OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);
					ENEMYS_POS[enemy_123 -1][1] = y;
					Draw_Cover(ENEMYS_POS[enemy_123][0],y);
					OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY, &err_os);

				}else{
					OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);	
				}
				if (ENEMYS_POS[0][0]== BOMBERMAN_POS_X && ENEMYS_POS[0][1] == BOMBERMAN_POS_Y)
				{
					Finish_Game();
				}
			}else{

				printf("DistanciaP %i e X %i \n ",distanceX,x);
				return;

			}



		} else{

			if((distanceX<= 0)&&(distanceY> 0)){


				if (find_wall_blocks(y,x) == false){
					printf("Distancia1a %i e Distancia2a  %i  X %i e Y %i \n ",distanceX,distanceY,x,y);
					Draw_Cover(ENEMYS_POS[enemy_123][0],y);
					OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY, &err_os);
					OSSemPend(&enemy[enemy_123-1],0,OS_OPT_PEND_BLOCKING, &ts,&err_os);
					x--;
					OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);
					ENEMYS_POS[enemy_123-1][0] = x;	
					OSSemPend(&enemy[enemy_123-1],0,OS_OPT_PEND_BLOCKING, &ts,&err_os);

					if (find_wall_blocks(y,x) == false){
						y++;
						OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);
						Draw_Cover(ENEMYS_POS[enemy_123][0],y);
						OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY, &err_os);
						ENEMYS_POS[enemy_123 -1][1] = y;
					}else{	
						y--;
						OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);

					}


					if (ENEMYS_POS[0][0]== BOMBERMAN_POS_X && ENEMYS_POS[0][1] == BOMBERMAN_POS_Y)
					{
						Finish_Game();
					}
				}else{
					//Olha no eixo y
					printf("DistanciaP %i e X %i \n ",distanceX,x);
					return;
				}

			} else{

				if((distanceX> 0)&&(distanceY> 0)){


					if (find_wall_blocks(y,x) == false){
						printf("Distancia1a %i e Distancia2a  %i  X %i e Y %i \n ",distanceX,distanceY,x,y);
						Draw_Cover(ENEMYS_POS[enemy_123][0],y);
						OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_DLY, &err_os);
						OSSemPend(&enemy[enemy_123-1],0,OS_OPT_PEND_BLOCKING, &ts,&err_os);
						x++;
						OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);
						ENEMYS_POS[enemy_123-1][0] = x;	
						OSSemPend(&enemy[enemy_123-1],0,OS_OPT_PEND_BLOCKING, &ts,&err_os);
						y++;

						if (find_wall_blocks(y,x) == false){
							OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);
							Draw_Cover(ENEMYS_POS[enemy_123][0],y);
							OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_DLY, &err_os);
							ENEMYS_POS[enemy_123 -1][1] = y;

						}else{
							y--;
							OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);

						}



						if (ENEMYS_POS[0][0]== BOMBERMAN_POS_X && ENEMYS_POS[0][1] == BOMBERMAN_POS_Y)
						{
							Finish_Game();
						}
					}else{

						printf("DistanciaP %i e X %i \n ",distanceX,x);
						return;

					}
				}else{
					if (find_wall_blocks(y,x) == false){
						printf("Distancia1a %i e Distancia2a  %i  X %i e Y %i \n ",distanceX,distanceY,x,y);
						Draw_Cover(ENEMYS_POS[enemy_123][0],y);
						OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_DLY, &err_os);
						OSSemPend(&enemy[enemy_123-1],0,OS_OPT_PEND_BLOCKING, &ts,&err_os);
						x++;
						OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);
						ENEMYS_POS[enemy_123-1][0] = x;	
						OSSemPend(&enemy[enemy_123-1],0,OS_OPT_PEND_BLOCKING, &ts,&err_os);
						y--;
						if (find_wall_blocks(y,x) == false){
							OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);
							Draw_Cover(ENEMYS_POS[enemy_123][0],y);
							OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_DLY, &err_os);
							ENEMYS_POS[enemy_123 -1][1] = y;
						}else{
							y++;
							OSSemPost(&enemy[enemy_123-1] ,OS_OPT_POST_NONE,&err_os);
						}


						if (ENEMYS_POS[0][0]== BOMBERMAN_POS_X && ENEMYS_POS[0][1] == BOMBERMAN_POS_Y)
						{
							Finish_Game();
						}
					}else{

						printf("DistanciaP %i e X %i \n ",distanceX,x);
						return;

					}

				}


			}
		}
	}
}