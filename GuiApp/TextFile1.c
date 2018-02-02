



if(directions[1] == 1){
	go_left(enemy_123,x,y);
}else{	
	if(directions[2] == 1){
		go_up(enemy_123,x,y);
	}else{	
		if(directions[4] == 1){
			go_down(enemy_123,x,y);
		}else{
			go_right(enemy_123,x,y);
		}
	}
}
			}else{
			}





			if(distanceX<0){

				if(directions[1] == 1){
					go_left(enemy_123,x,y);
				}else{	
					if(directions[2] == 1){
						go_up(enemy_123,x,y);
					}else{	
						if(directions[4] == 1){
							go_down(enemy_123,x,y);
						}else{
							if(directions[3] == 1){
								go_right(enemy_123,x,y);
							}else{	
								return;
							}
						}

					}
				}
			}else{
				if(distanceX>0){

					if(directions[3] == 1){
						go_right(enemy_123,x,y);
					}else{	
						if(directions[2] == 1){
							go_up(enemy_123,x,y);
						}else{	
							if(directions[4] == 1){
								go_down(enemy_123,x,y);
							}else{
								if(directions[1] == 1){
									go_left(enemy_123,x,y);
								}else{	
									return;
								}

							}
						}
					}
				}else{	
					return;
				}
			}

			if(distanceY<0){

				if(directions[2] == 1){
					go_up(enemy_123,x,y);
				}else{	
					if(directions[1] == 1){
						go_left(enemy_123,x,y);
					}else{	
						if(directions[3] == 1){
							go_right(enemy_123,x,y);
						}else{
							if(directions[4] == 1){
								go_down(enemy_123,x,y);
							}else{
								return;
							}
						}
					}
				}
			}else{
				if(distanceY>0){
					if(directions[4] == 1){
						go_down(enemy_123,x,y);
					}else{	
						if(directions[1] == 1){
							go_left(enemy_123,x,y);
						}else{	
							if(directions[3] == 1){
								go_right(enemy_123,x,y);
							}else{
								if(directions[2] == 1){
									go_up(enemy_123,x,y);
								}else{
									return;
								}
							}

						}

					}
				}else{	
					return;
				}
			}


			bool find_wall_blocks(int i, int j){


				if((LABIRINTO[j][i] == 2)||(LABIRINTO[j][i] == 1)||(LABIRINTO[j][i] == 6)){ // Se tem bloco, paredes, ou bombas
					printf("Posicao do bloco ou parede true  X %i , Y %i \n",i , j);
					return true;

				}else
				{
					printf("Posicao do bloco ou parede false X %i , Y %i \n",i , j);
					return false;

				}


			}