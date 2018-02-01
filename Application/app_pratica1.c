
/*
*********************************************************************************************************
*
*                                          APPLICATION CODE - BCC722
*
*                                         TARGET = Microsoft Windows
*
* Arquivo			: app.c
* Versao			: V1.0
* Aluno(s)			: Diego dos Santos Carneiro
* Data				: 02/12/2017
* Pratica			: PRATICA_1
* Descricao			:		
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <app_cfg.h>
#include  <os.h>
#include  <os_cfg_app.h>

// biblioteca GUI
#include "gui.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/

//Enumeracao dos Objetos Graficos

enum GRAPHIC_OBJS{
	ID_BUTTON_1 = 0,
	ID_EDIT_LINE_1,
};


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

//Criacao da Indentificacao das tarefas nas Structs do Processador e do OS
static  OS_TCB   AppStartTaskTCB;
static  CPU_STK  AppStartTaskStk[APP_TASK_START_STK_SIZE];
static  OS_TCB   AppTask1TCB;
static  CPU_STK  AppTask1Stk[APP_TASK_START_STK_SIZE];
static  OS_TCB   AppTask2TCB;
static  CPU_STK  AppTask2Stk[APP_TASK_START_STK_SIZE];
static  OS_TCB   AppTask3TCB;
static  CPU_STK  AppTask3Stk[APP_TASK_START_STK_SIZE];
static  OS_TCB   AppRedrawingTCB;
static  CPU_STK  AppRedrawingStk[APP_TASK_START_STK_SIZE];

// imagens usadas no programa
HBITMAP * img;
int imgXPos, imgYPos;
static OS_MUTEX teste;

/*
*********************************************************************************************************
*                                       EXTERN VARIABLES
*********************************************************************************************************
*/

//Handlers Graficos
extern HWND hwnd; // Variaveis declaradas do modulo da GUI
extern HDC hdc;
extern MSG Msg;

/*
*********************************************************************************************************
*                                            LOCAL MACRO'S
*********************************************************************************************************
*/

#define  APP_TASK_STOP();                             { while (DEF_ON) { \
	;            \
}                \
}


#define  APP_TEST_FAULT(err_var, err_code)            { if ((err_var) != (err_code)) {   \
	APP_TASK_STOP();             \
}                                \
}


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*Tarefa Inicial*/
static  void  App_TaskStart (void  *p_arg);

/*Tarefa de Criacao dos Pixels*/ 
static  void  App_Task1 (void  *p_arg);
static  void  App_Task2 (void *p_arg);
static  void  App_Task3 (void  *p_arg);

/*Tarefa para desenhar a imagem */
static  void  App_Redrawing (void *p_arg);

//Chamada dos CALLBACKS graficos, responsivos aos eventos
LRESULT CALLBACK HandleGUIEvents(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*
*********************************************************************************************************
*                                               main()
*
* Description : Funcao principal do programa.
*
* Arguments   : none.
*
* Returns     : none.
*
* Note(s)     : Cria a Tarefa Principal no OS
*********************************************************************************************************
*/

int  main (void){

	OS_ERR  err_os;

	OSInit(&err_os);                                            /* inicializa uC/OS-III.                                */
	APP_TEST_FAULT(err_os, OS_ERR_NONE);

	OSTaskCreate((OS_TCB     *)&AppStartTaskTCB,                /* Cria a tarefa inicial.                             */
		(CPU_CHAR   *)"App Start Task",
		(OS_TASK_PTR ) App_TaskStart,
		(void       *) 0,
		(OS_PRIO     ) APP_TASK_START_PRIO,
		(CPU_STK    *)&AppStartTaskStk[0],
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10u,
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
		(OS_MSG_QTY  ) 0u,
		(OS_TICK     ) 0u,
		(void       *) 0,
		(OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err_os);
	APP_TEST_FAULT(err_os, OS_ERR_NONE);


	OSStart(&err_os);                                           /* Inicia o funcionamento do escalonador. */
	APP_TEST_FAULT(err_os, OS_ERR_NONE);
}

/*
*********************************************************************************************************
*                                           App_Task[1,2,3]()
*
* Description : Tarefas de Criacao dos Pixels.
*
* Arguments   : p_arg       Argumento passado a 'OSTaskCreate()'.
*
* Returns     : none.
*
* Created by  : App_TaskStart().
*
*********************************************************************************************************
*/

static  void  App_Task1 (void  *p_arg){
	int i=0;
	OS_ERR  err_os;

	while (1){

		for(i=0;i<500;i++) //Pintar 500 Pixels ao longo da tela[Tal valor nao ultrapassa o video]
			GUI_PutPixel(0+i,100,RGB(255,0,0)); //Linha 100, Coluna 0 , Cor Vermelha
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY, &err_os); //Utilizar a Funcao Delay do Sistema por 500ms
	}	
}

static  void  App_Task2 (void  *p_arg){
	int i=0;
	OS_ERR  err_os;

	while (1){
		for(i=0;i<500;i++) //Pintar 500 Pixels ao longo da tela[Tal valor nao ultrapassa o video]
			GUI_PutPixel(0+i,200,RGB(0,255,0)); //Linha 200, Coluna 0 , Cor Verde
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY, &err_os); //Utilizar a Funcao Delay do Sistema por 500ms
	}	
}

static  void  App_Task3 (void  *p_arg){
	int i=0;
	OS_ERR  err_os;

	while (1) {

		for(i=0;i<500;i++) //Pintar 500 Pixels ao longo da tela[Tal valor nao ultrapassa o video]
			GUI_PutPixel(0+i,300,RGB(255,0,0)); //Linha 300, Coluna 0 , Cor Vermelha
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_DLY, &err_os); //Utilizar a Funcao Delay do Sistema por 500ms
	}	
}

/*
*********************************************************************************************************
*                                           App_Redrawing()
*
* Description : Tarefa responsavel por desenhar a figura a cada 2 segundos.
*
* Arguments   : p_arg       Argumento passado a 'OSTaskCreate()'.
*
* Returns     : none.
*
* Created by  : App_TaskStart().
*
*********************************************************************************************************
*/

static void App_Redrawing (void *p_arg){

	int i=0;
	OS_ERR  err_os;
	img = GUI_CreateImage( "r2d2.bmp", 100, 100);
	// coloca uma imagem de largura 100 x 100

	while(1){

		int randomX = rand() % 500; //Posicao Randomica X no maximo 500 para nao sair da tela e nao esbarrar no botao ou Edit Label
		int randomY = rand() % 400; //Posicao Randomica Y no maximo 450 para nao sair da tela e nao esbarrar no botao ou Edit Label

		GUI_DrawImage(img, randomX, randomY, 100, 100,1); // Desenha a imagem em uma posicao randomica

		OSTimeDlyHMSM(0,0,0,2000,OS_OPT_TIME_DLY, &err_os); //Delay de 2 segundos

	}
}

/*
*********************************************************************************************************
*                                           App_TaskStart()
*
* Description : Exemplo de tarefa Inicial do sistema.
*
* Arguments   : p_arg       Argumento passado a 'OSTaskCreate()'.
*
* Returns     : none.
*
* Created by  : main().
*
*********************************************************************************************************
*/

static  void  App_TaskStart (void  *p_arg){

	int i=0;
	int erroN;
	CPU_CHAR ts;
	OS_ERR  err_os;

	erroN = GUI_Init(HandleGUIEvents);	// inicializa a interface grafica
	OSMutexCreate(&teste, &ts,&err_os);

	if( erroN < 0 ) { // se falhou para carregar a Gui, retorna.
		printf("\n Erro ao iniciar a Gui (%d)",erroN);
	}

	GUI_CreateEditLine(0,500, 200, ID_EDIT_LINE_1);						// cria um LineEdit
	GUI_CreateButton(600, 500, 100, 30, "OK", ID_BUTTON_1);				// Cria um botao

	/*Criacao da tarefa de deseho*/

	OSTaskCreate((OS_TCB     *)&AppRedrawingTCB,                                          
		(CPU_CHAR   *)"App StartRedrawing",
		(OS_TASK_PTR ) App_Redrawing,
		(void       *) 0,
		(OS_PRIO     ) 10, //Define a prioridade da tarefa
		(CPU_STK    *)&AppRedrawingStk[0],
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10u,
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
		(OS_MSG_QTY  ) 0u,
		(OS_TICK     ) 0u,
		(void       *) 0,
		(OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err_os);
	APP_TEST_FAULT(err_os, OS_ERR_NONE);

	/* Criacao da Tarefa de Pixels */

	OSTaskCreate((OS_TCB     *)&AppTask1TCB,                                          
		(CPU_CHAR   *)"App Start1",
		(OS_TASK_PTR ) App_Task1,
		(void       *) 0,
		(OS_PRIO     ) 10,
		(CPU_STK    *)&AppTask1Stk[0],
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10u,
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
		(OS_MSG_QTY  ) 0u,
		(OS_TICK     ) 0u,
		(void       *) 0,
		(OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err_os);
	APP_TEST_FAULT(err_os, OS_ERR_NONE);

	OSTaskCreate((OS_TCB     *)&AppTask2TCB,                                             
		(CPU_CHAR   *)"App Start2",
		(OS_TASK_PTR ) App_Task2,
		(void       *) 0,
		(OS_PRIO     ) 10,
		(CPU_STK    *)&AppTask2Stk[0],
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10u,
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
		(OS_MSG_QTY  ) 0u,
		(OS_TICK     ) 0u,
		(void       *) 0,
		(OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err_os);
	APP_TEST_FAULT(err_os, OS_ERR_NONE);

	OSTaskCreate((OS_TCB     *)&AppTask3TCB,               
		(CPU_CHAR   *)"App Start3",
		(OS_TASK_PTR ) App_Task3,
		(void       *) 0,
		(OS_PRIO     ) 10,
		(CPU_STK    *)&AppTask3Stk[0],
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10u,
		(CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
		(OS_MSG_QTY  ) 0u,
		(OS_TICK     ) 0u,
		(void       *) 0,
		(OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		(OS_ERR     *)&err_os);
	APP_TEST_FAULT(err_os, OS_ERR_NONE);

	/* Fim da Tarefa de Pixels */

	printf("\n Inicio do loop de msg");

	// Loop de mensagens para interface grafica
	while (1){
		PeekMessage(&Msg, 0, 0, 0, PM_REMOVE);

		TranslateMessage(&Msg);
		DispatchMessage(&Msg);

		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_DLY, &err_os);
	}

	printf("\n fim do loop de msg");

	DeleteObject(img);

}


// Step 4: CallBacks da Janela
LRESULT CALLBACK HandleGUIEvents(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	int i;
	switch(msg){
		//Caso haver um comando de mouse		
	case WM_COMMAND:{

		if(((HWND)lParam) && (HIWORD(wParam) == BN_CLICKED)){
			int iMID;
			char *text;
			iMID = LOWORD(wParam);
			text = GUI_GetTextEditLine(ID_EDIT_LINE_1);

			switch(iMID){
			case ID_BUTTON_1:{
				MessageBox(hwnd, (LPCTSTR)text,  (LPCTSTR) "Mensagem", MB_OK|MB_ICONEXCLAMATION);

				break;
							 }
			default:
				break;
			}
		}
		break;
	}

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;


	case WM_PAINT: {

				   }
				   return DefWindowProc(hwnd, msg, wParam, lParam);
				   break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN: 
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;

	case WM_MOUSEMOVE:
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;

	case WM_LBUTTONUP:
		//ReleaseCapture(); // User released mouse button, so no need to keep track of global mouse events.
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;

	case WM_CAPTURECHANGED: 
		// The mouse capture window has changed. If the new capture window is not this window, then we need to stop rotation/whatever.
		//if( (HWND)lParam != hWnd )
		//{
		//   EndMousing();
		//}
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;

}