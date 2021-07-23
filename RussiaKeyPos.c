#include "stdafx.h"
#include "../inc/global.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "md5.h"


#ifdef WIN32
void DownLoadByUdisk(void){}
#endif


unsigned int hash(const char *word)
{
    unsigned int hash = 5381678965;
    int c;

    while ((c = *word++))        // *str++ is going to the next address in memory, where the next char in the string is stored
    {
        if (isupper(c))
        {
            c = c + 32;
        }

        hash = ((hash << 5) + hash) + c; // hash * 33 + c   // hash << 5 = hash * 2^5
    }
		return hash % 1000000000;
}

int hashString(){

	unsigned int i=0;
	char output[81];

	char finalString[100];
	char DAC[30];
	char* cardNum="9998267356826699729";
	char* cardPanNum="83";
	char* expDate="270929";
	char* actDate="210929";
	char* userName="Servicios Paguetodo";
	char* userControlNum="10110";

	strcpy(DAC, cardNum);
	strcat(DAC, cardPanNum);

	memmove(DAC, DAC+13, strlen(DAC));

	strcpy(finalString, cardNum);
	strcat(finalString, userControlNum);
	strcat(finalString, cardPanNum);
	strcat(finalString, DAC);
	strcat(finalString, userName);
	strcat(finalString, expDate);
	strcat(finalString, actDate);

	i=hash(finalString);

	sprintf(output, "%d", i);

	//WriteFile_Api(CONFIG_FILE_IN, (unsigned char *)output, 0, strlen(output));
}

int FindPacketTagValue(char *inData, char *Tag, char *OutValue)
{
	char *p=NULL, *q=NULL;

	if (inData == NULL || Tag == NULL || OutValue == NULL)
		return -1;

	p = strstr(inData, Tag);
	if (p == NULL)
	{
		ScrCls_Api();
		ErrorPrompt("keyset format error", 3);
		return -2;
	}
	q = strchr(p+strlen(Tag)+2, '\"');
	if (q == NULL)
	{
		ScrCls_Api();
		ErrorPrompt("keyset format error", 3);
		return -3;
	}
	memcpy(OutValue, p+strlen(Tag)+2, q-(p+strlen(Tag)+2));

	return 0;
}

int printAvailableInjections(void){
	int k=0, downloadValue=0;
	char str3[30], str4[10], downloads[20], packFileText[200];
	FILE *fp;

	fp = fopen (CONFIG_FILE_IN, "r"); fgets (packFileText, 100, fp);

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe archivo", 3);
		return -2;
	}
		 fclose(fp);

	strcpy(downloads, strtok(packFileText , " "));

	memmove(downloads, downloads+12, strlen(downloads));
	
	downloadValue= atoi(downloads);

	k=20000-downloadValue;

	sprintf(str4, "%d", k);

	strcpy(str3, "Inyec.disp: ");
	strcat(str3, str4);

	ScrClrLine_Api(LINE2, LINE6);
	ErrorPrompt(str3, 5);
	return -1;
}

int printNumberInjections(void){

	char str[30], downloads[20], packFileText[200];
	FILE *fp;

	fp = fopen (CONFIG_FILE_IN, "r"); fgets (packFileText, 100, fp);

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe archivo", 3);
		return -2;
	}
		 fclose(fp);

	strcpy(downloads, strtok(packFileText , " "));

	memmove(downloads, downloads+12, strlen(downloads));

	strcpy(str, "Inyec.realizadas:");
	strcat(str, downloads);

	ScrClrLine_Api(LINE2, LINE6);
	ErrorPrompt(str, 5);
	return -1;
}

int printOperPhysicalStatus(char *KeyFileName){

	FILE *fp;
	int i=0, j=0, k=0, g=0, downloadValue=0;
	char date[30], temp[80];
	char str[30], str3[30], str4[10], printBuf[20000], printBuf2[20000], packFileText [200], packFileText2[200],trash[20],downloads[20],downloads2[20],packName[20], packNumber[20], amountComp[20], keysLong[20], values[200][141], valuesFinalCopy[200][141], valuesFinalCopy2[200][141], valuesCopy[200][141];

	fp = fopen (CONFIG_FILE_IN, "r"); fgets (packFileText2, 100, fp);

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe config", 3);
		return -2;
	}else{
	fclose(fp);
	}

	strcpy(downloads2, strtok(packFileText2 , " "));

	fp = fopen (KeyFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe paquete", 3);
		return -2;
	}

	while(fgets(values[i], 141, fp) != NULL) 
	{
		for (j = 0; values[i][j] && isspace(values[i][j]); j++)
			;
		if (values[i][j] == '*' || values[i][j] == '\0')
			continue;
        i++;
    }
	if(fp!=NULL){
	fclose(fp);
	}

	fp = fopen (KeyFileName, "r"); fgets (packFileText, 100, fp); fclose(fp);

	strcpy(trash, strtok(packFileText , " "));
	strcpy(downloads, strtok(NULL , " "));
    strcpy(packName, strtok(NULL , " "));
	strcpy(packNumber, strtok(NULL, " "));
	strcpy(amountComp , strtok(NULL, " "));
	strcpy(keysLong, strtok(NULL, " "));

	strcpy(date,__DATE__);
	strcat(date," ");
	strcat(date,__TIME__);
	strcat(date, "\n");

	strcpy(str, "App:" );
	strcat(str, (char*)App_Msg.Version);
	strcat(str, "\r\n");

	strcpy(printBuf, "Cargador de llaves\nMenu Operador\nEstatus Carga Llaves\n*******Config*******\nOperador\nImpresion\nS/N:000185237789\n");
	strcat(printBuf, str);
	strcat(printBuf, date);
	strcat(printBuf, packName);
	strcat(printBuf, "\n");
	strcat(printBuf, "Indice de llaves: 00\n");

		for(g=0;g<=200;g++){

			if(strcmp(keysLong, "keysLong=32\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][113]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+105, strlen(valuesCopy[g]));

				strcat(printBuf, "BDK KCV:");
				strcat(printBuf, valuesCopy[g]);
				strcat(printBuf, "\nKSI:");
				strcat(printBuf, values[g]);
				strcat(printBuf, "\n");
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][112]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+106, strlen(valuesCopy[g]));

				strcpy(printBuf2, "KIN:");
				strcat(printBuf2, values[g]);
				strcat(printBuf2, "\nKCV:");
				strcat(printBuf2, valuesCopy[g]);
				strcat(printBuf2, "\n");
				strcat(printBuf, printBuf2);

			}
		}

			if(strcmp(keysLong, "keysLong=48\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][129]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+121, strlen(valuesCopy[g]));

				strcat(printBuf, "BDK KCV:");
				strcat(printBuf, valuesCopy[g]);
				strcat(printBuf, "\nKSI:");
				strcat(printBuf, values[g]);
				strcat(printBuf, "\n");
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][128]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+122, strlen(valuesCopy[g]));

				strcpy(printBuf2, "KIN:");
				strcat(printBuf2, values[g]);
				strcat(printBuf2, "\nKCV:");
				strcat(printBuf2, valuesCopy[g]);
				strcat(printBuf2, "\n");
				strcat(printBuf, printBuf2);
			}
		}
	}

		memmove(downloads2, downloads2+12, strlen(downloads2));
	
		downloadValue= atoi(downloads2);

		k=20000-downloadValue;

		sprintf(str4, "%d", k);

		strcat(printBuf, "Max.inyecciones:20000\n");

		strcpy(str, "Inyec.realizadas:");
		strcat(str, downloads2);
		strcat(str, "\n");

		strcat(printBuf, str);

		strcpy(str3, "Inyec.disp: ");
		strcat(str3, str4);

		strcat(printBuf, str3);

		PrnClrBuff_Api();

		PrnStr_Api(printBuf);

		PrnStart_Api();


}

 int InputPacketOperPhysicalGetInfo(void)
{
	char Tempbuf[10],KeyFileName[100];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));
		strcpy(KeyFileName, "");
		strcat(KeyFileName, "/mtd0/dll/");
		strcat(KeyFileName, Tempbuf);
		strcat(KeyFileName, ".xml");

		while(KeyFileName[0]!='/'){

			memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

		}
		if(KeyFileName[0]=='/'){
			printOperPhysicalStatus(KeyFileName);
		}
	}
}

int displayOperPackInfo(char values[][141],char values2[][141], char *KeyFileName, char *packName, char *packNumber, char *amountComp, char *keysLong){

	int i=3, j=4, k=0, downloadValue=0;
	char temp[80], str[30], str3[30], str4[10], downloads[20], packFileText[200];
	FILE *fp;

	fp = fopen (CONFIG_FILE_IN, "r"); fgets (packFileText, 100, fp);

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe archivo", 3);
		return -2;
	}
		 fclose(fp);

	strcpy(downloads, strtok(packFileText , " "));

	memmove(downloads, downloads+12, strlen(downloads));
	
	downloadValue= atoi(downloads);

	k=20000-downloadValue;

	sprintf(str4, "%d", k);

	strcpy(str, "Inyec.realizadas:");
	strcat(str, downloads);

	strcpy(str3, "Inyec.disp: ");
	strcat(str3, str4);

	while(WaitAnyKey_Api(60)!=ESC && i<=200){

		if(!strstr(values[i],"ÌÌÌÌÌÌÌÌÌÌÌ")){
			if(strstr(values[i],"BDK")){

				strcpy(temp,values[i]);

				temp[16]=0;

				ScrClrLine_Api(LINE2, LINE6);
				ScrDisp_Api(LINE2, 0, packName, FDISP|LDISP);
				ScrDisp_Api(LINE3, 0, "Indice de llaves: 00", FDISP|LDISP);
				ScrDisp_Api(LINE4, 0, temp, FDISP|LDISP);

				memmove(values[i], values[i]+18, strlen(values[i]));
				ScrDisp_Api(LINE5, 0, values[i], FDISP|LDISP);


			}
		}

		if(strstr(values[i],"ÌÌÌÌÌÌÌÌÌÌÌ")||strstr(values[i],"BDK")==NULL){
			

			while(WaitAnyKey_Api(60)!=ESC && j<=200){

				if(!strstr(values2[j],"ÌÌÌÌÌÌÌÌÌÌÌ")){
					if(strstr(values2[j],"KIN")){

						strcpy(temp,values2[j]);

						temp[9]=0;

						ScrClrLine_Api(LINE2, LINE6);
						ScrDisp_Api(LINE2, 0, temp, FDISP|LDISP);

						memmove(values2[j], values2[j]+9, strlen(values2[j]));
						ScrDisp_Api(LINE3, 0, values2[j], FDISP|LDISP);

					}
				}
			
					if(strstr(values2[j],"ÌÌÌÌÌÌÌÌÌÌÌ") && strstr(values2[j],"KIN")==NULL){
						ScrClrLine_Api(LINE2, LINE2);
						ScrDisp_Api(LINE3, 0, "Max.inyec:20000", FDISP|LDISP);
						ScrDisp_Api(LINE4, 0, str, FDISP|LDISP);
						ScrDisp_Api(LINE5, 0, str3, FDISP|LDISP);

						if(WaitAnyKey_Api(60)==ESC){
							return ESC;
						}
					}

				ScrBrush_Api();
				KBFlush_Api();
				j=j+1;

				}
		}
	
		ScrBrush_Api();
		KBFlush_Api();

		i=i+1;
	}

}

int displayDownloadOperInfo(char values[][141],char values2[][141], char *KeyFileName, char *packName, char *packNumber, char *amountComp, char *keysLong){

	int i=0;
	char date[30], str[30];
	
	strcpy(date,__DATE__);
	strcat(date," ");
	strcat(date,__TIME__);

	strcpy(str, "App:" );
	strcat(str, (char*)App_Msg.Version);

	while(WaitAnyKey_Api(60)!=ESC && i<=200){

		ScrClrLine_Api(LINE2, LINE6);

		ScrDisp_Api(LINE2, 0, "Impresion:", FDISP|LDISP);

		ScrDisp_Api(LINE3, 0, "S/N:000185237789", FDISP|LDISP);

		ScrDisp_Api(LINE4, 0, str, FDISP|LDISP);

		ScrDisp_Api(LINE5, 0, date, FDISP|LDISP);

		KBFlush_Api();

		if(WaitAnyKey_Api(60)==ENTER){
			displayOperPackInfo(values, values2, KeyFileName, packName, packNumber, amountComp, keysLong);
		}
		if(WaitAnyKey_Api(60)==ESC){
			return ESC;
		}
			
	}
}

int printPackOperStatus(char values[][141], char *KeyFileName, char *packName, char *packNumber, char *amountComp, char *keysLong)
{
	int g=1;
	char valuesCopy[200][141];
	char valuesFinalCopy[200][141];
	char valuesFinalCopy2[200][141];

	for(g=0;g<=200;g++){

		if(strcmp(keysLong, "keysLong=32\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][114]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+105, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy[g], "BDK KCV:");
				strcat(valuesFinalCopy[g], valuesCopy[g]);
				strcat(valuesFinalCopy[g], " KSI:");
				strcat(valuesFinalCopy[g], values[g]);
				valuesFinalCopy[g][40]='\0';
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][112]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+106, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy2[g], "KIN:");
				strcat(valuesFinalCopy2[g], values[g]);
				strcat(valuesFinalCopy2[g], " KCV:");
				strcat(valuesFinalCopy2[g], valuesCopy[g]);
				valuesFinalCopy2[g][30]='\0';
			}
		}

		if(strcmp(keysLong, "keysLong=48\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][130]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+121, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy[g], "BDK KCV:");
				strcat(valuesFinalCopy[g], valuesCopy[g]);
				strcat(valuesFinalCopy[g], " KSI:");
				strcat(valuesFinalCopy[g], values[g]);
				valuesFinalCopy[g][40]='\0';
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][128]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+122, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy2[g], "KIN:");
				strcat(valuesFinalCopy2[g], values[g]);
				strcat(valuesFinalCopy2[g], " KCV:");
				strcat(valuesFinalCopy2[g], valuesCopy[g]);
				valuesFinalCopy2[g][40]='\0';
			}
		}

	}

	while(1)
	{	

	DispTitle("Cargador de llaves");

	ScrClrLine_Api(LINE2, LINE6);

	ScrDisp_Api(LINE2, 0, "Menu Operador", FDISP|CDISP);
	ScrDisp_Api(LINE3, 0, "Estatus Carga Llaves", FDISP|CDISP);
	ScrDisp_Api(LINE4, 0, "*******Config*******", FDISP|CDISP);
	ScrDisp_Api(LINE5, 0, "Operador", FDISP|CDISP);
	ScrBrush_Api();

	KBFlush_Api();

		if(WaitAnyKey_Api(60)==ENTER){
			displayDownloadOperInfo(valuesFinalCopy, valuesFinalCopy2, KeyFileName, packName, packNumber, amountComp, keysLong);
		}
		if(WaitAnyKey_Api(60)==ESC){
			return ESC;
		}

}
	return 0;
}

   int findPackOperValues(char *KeyFileName){

	FILE *fp;
	int i=0, j=0;
	char values[200][141], packFileText [200];
	char trash[20],downloads[20], packName[20], packNumber[20], amountComp[20], keysLong[20];

	fp = fopen (KeyFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt(KeyFileName, 3);
		return;
	}else{
		fgets (packFileText, 100, fp);
		strcpy(trash, strtok(packFileText , " "));
		strcpy(downloads, strtok(NULL , " "));
		strcpy(packName, strtok(NULL , " "));
		strcpy(packNumber, strtok(NULL, " "));
		strcpy(amountComp , strtok(NULL, " "));
		strcpy(keysLong, strtok(NULL, " "));
		fclose(fp);
	}


	fp = fopen (KeyFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt(KeyFileName, 3);
		return;
	}else{

		while(fgets(values[i], 141, fp) != NULL) 
		{
			for (j = 0; values[i][j] && isspace(values[i][j]); j++)
				;
			if (values[i][j] == '*' || values[i][j] == '\0')
				continue;
			i=i+1;
		}

			fclose(fp);
	}

	printPackOperStatus(values, KeyFileName, packName, packNumber, amountComp, keysLong);

}

 int InputPacketOperGetInfo(void)
{
	char Tempbuf[10],KeyFileName[100];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));
		strcpy(KeyFileName, "");
		strcpy(KeyFileName, "‪/mtd0/dll/");
		strcat(KeyFileName, Tempbuf);
		strcat(KeyFileName, ".xml");

		while(KeyFileName[0]!='/'){

			memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

		}
		if(KeyFileName[0]=='/'){
			findPackOperValues(KeyFileName);
		}

	}
}

 int displayKeys(char values[][141],char values2[][141], char *KeyFileName, char *packName, char *packNumber, char *amountComp, char *keysLong){

	int i=3, j=4;
	char temp[80];

	while(WaitAnyKey_Api(60)!=ESC && i<=200){

		if(!strstr(values[i],"ÌÌÌÌÌÌÌÌÌÌÌ")){
			if(strstr(values[i],"BDK")){

				strcpy(temp,values[i]);

				temp[16]=0;

				ScrClrLine_Api(LINE2, LINE6);
				ScrDisp_Api(LINE2, 0, packName, FDISP|LDISP);
				ScrDisp_Api(LINE3, 0, temp, FDISP|LDISP);

				memmove(values[i], values[i]+18, strlen(values[i]));
				ScrDisp_Api(LINE4, 0, values[i], FDISP|LDISP);

			}
		}

		if(strstr(values[i],"ÌÌÌÌÌÌÌÌÌÌÌ")||!strstr(values[i],"BDK")){
		
			ScrDisp_Api(LINE2, 0, packName, FDISP|LDISP);
			while(WaitAnyKey_Api(60)!=ESC && j<=200){

			if(!strstr(values2[j],"ÌÌÌÌÌÌÌÌÌÌÌ") ){
				if(strstr(values2[j],"KIN")){

					strcpy(temp,values2[j]);

					temp[9]=0;

					ScrClrLine_Api(LINE2, LINE6);
					ScrDisp_Api(LINE2, 0, temp, FDISP|LDISP);

					memmove(values2[j], values2[j]+9, strlen(values2[j]));
					ScrDisp_Api(LINE3, 0, values2[j], FDISP|LDISP);

				}

			}
			
				if(strstr(values2[j],"ÌÌÌÌÌÌÌÌÌÌÌ")||!strstr(values2[i],"KIN")){
						
					if(WaitAnyKey_Api(60)==ESC){
							return ESC;
					}
				}

			ScrBrush_Api();
			j=j+1;
			}
		}
	
		ScrBrush_Api();

		i=i+1;
	}

}

 int displayDownloadInfo(char values[][141],char values2[][141], char *KeyFileName, char *downloads, char *packName, char *packNumber, char *amountComp, char *keysLong){

	int i=0;
	char str4[40];

	strcpy(str4, "Num. descargas: ");
	memmove(downloads, downloads+10, strlen(downloads));
	strcat(str4, downloads);

	while(WaitAnyKey_Api(60)!=ESC && i<=200){

		ScrClrLine_Api(LINE2, LINE6);

		ScrDisp_Api(LINE2, 0, "S/N:000185237789", FDISP|LDISP);

		ScrDisp_Api(LINE3, 0, "Max.descargas:20000", FDISP|LDISP);

		ScrDisp_Api(LINE4, 0, str4, FDISP|LDISP);

		KBFlush_Api();

		if(WaitAnyKey_Api(60)==ENTER){
			displayKeys(values, values2, KeyFileName, packName, packNumber, amountComp, keysLong);
		}
		if(WaitAnyKey_Api(60)==ESC){
			return ESC;
		}
			
	}
}

 int printKeyStatus(char values[200][141], char *KeyFileName, char *downloads, char *packName, char *packNumber, char *amountComp, char *keysLong)
{
	int g=1;
	char date[30];
	char valuesCopy[200][141];
	char valuesFinalCopy[200][141];
	char valuesFinalCopy2[200][141];

	strcpy(date,__DATE__);
	strcat(date," ");
	strcat(date,__TIME__);

	for(g=1;g<=200;g++){

		if(strcmp(keysLong, "keysLong=32\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][114]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+105, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy[g], "BDK KCV:");
				strcat(valuesFinalCopy[g], valuesCopy[g]);
				strcat(valuesFinalCopy[g], " KSI:");
				strcat(valuesFinalCopy[g], values[g]);
				valuesFinalCopy[g][40]='\0';
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][112]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+106, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy2[g], "KIN:");
				strcat(valuesFinalCopy2[g], values[g]);
				strcat(valuesFinalCopy2[g], " KCV:");
				strcat(valuesFinalCopy2[g], valuesCopy[g]);
				valuesFinalCopy2[g][30]='\0';
			}
		}

		if(strcmp(keysLong, "keysLong=48\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][130]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+121, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy[g], "BDK KCV:");
				strcat(valuesFinalCopy[g], valuesCopy[g]);
				strcat(valuesFinalCopy[g], " KSI:");
				strcat(valuesFinalCopy[g], values[g]);
				valuesFinalCopy[g][40]='\0';
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][128]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+122, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy2[g], "KIN:");
				strcat(valuesFinalCopy2[g], values[g]);
				strcat(valuesFinalCopy2[g], " KCV:");
				strcat(valuesFinalCopy2[g], valuesCopy[g]);
				valuesFinalCopy2[g][40]='\0';
			}
		}

	}

	while(1)
	{	

	DispTitle("Cargador de llaves");

	ScrClrLine_Api(LINE2, LINE6);

	ScrDisp_Api(LINE2, 0, "Menu Admin", FDISP|CDISP);
	ScrDisp_Api(LINE3, 0, "Estatus Llaves", FDISP|CDISP);
	ScrDisp_Api(LINE4, 0, "*******Config*******", FDISP|CDISP);
	ScrDisp_Api(LINE5, 0, date, FDISP|CDISP);
	ScrBrush_Api();


		if(WaitAnyKey_Api(60)==ENTER){
			displayDownloadInfo(valuesFinalCopy, valuesFinalCopy2, KeyFileName,downloads, packName, packNumber, amountComp, keysLong);
		}
		if(WaitAnyKey_Api(60)==ESC){
			return ESC;
		}

}
	return 0;
}

   int findPackKeysValues(char *KeyFileName, char *downloads,char *packName, char *packNumber, char *amountComp, char *keysLong){

	FILE *fp;
	int i=0, j=0;
	char values[200][141];

	fp = fopen (KeyFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe paquete", 3);
		return;
	}

	while(fgets(values[i], 141, fp) != NULL) 
	{
		for (j = 0; values[i][j] && isspace(values[i][j]); j++)
			;
		if (values[i][j] == '*' || values[i][j] == '\0')
			continue;
        i++;
    }

	if(fp==NULL){
		fclose(fp);
	}
	
	printKeyStatus(values, KeyFileName, downloads, packName, packNumber, amountComp, keysLong);

}

  int getVal(char *KeyFileName){

	FILE *fp;
	char trash[20], downloads[20], packName[20], packNumber[20], amountComp[20], keysLong[20],  packFileText[200];

	  	fp = fopen (KeyFileName, "r");
	
		if(fp==NULL){
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("no existe paquete", 3);
			return;
		}else{

		fgets (packFileText, 100, fp); 

		fclose(fp);
		}

		strcpy(trash, strtok(packFileText , " "));
		strcpy(downloads, strtok(NULL , " "));
		strcpy(packName, strtok(NULL , " "));
		strcpy(packNumber, strtok(NULL, " "));
		strcpy(amountComp , strtok(NULL, " "));
		strcpy(keysLong, strtok(NULL, " "));


		findPackKeysValues(KeyFileName, downloads, packName, packNumber, amountComp, keysLong);
   }

 int InputPacketKeysGetInfo(void)
{
	char Tempbuf[10],KeyFileName[100];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));

		strcpy(KeyFileName, "‪");
		strcat(KeyFileName, "‪/mtd0/dll/");
		strcat(KeyFileName, Tempbuf);
		strcat(KeyFileName, ".xml");

		while(KeyFileName[0]!='/'){

			memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

		}
		if(KeyFileName[0]=='/'){
			getVal(KeyFileName);
		}

	}
}

 
int printPhysicalStatus(char *KeyFileName){

	FILE *fp;
	int i=0, j=0, g=0;
	char date[30];
	char str[30], str3[30], str5[40], printBuf[20000], printBuf2[20000], packFileText[200],trash[20],downloads[20], packName[20],packNumber[20], amountComp[20], keysLong[20], values[200][141],valuesCopy[200][141], valuesFinalCopy[200][141], valuesFinalCopy2[200][141];

	fp = fopen (KeyFileName, "r"); 
	
	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe paquete", 3);
		return;
	}else{
	fgets (packFileText, 100, fp); fclose(fp);
	}

	strcpy(trash, strtok(packFileText , " "));
	strcpy(downloads, strtok(NULL , " "));
	strcpy(packName, strtok(NULL , " "));
	strcpy(packNumber, strtok(NULL , " "));
	strcpy(amountComp, strtok(NULL , " "));
	strcpy(keysLong, strtok(NULL , " "));

	fp = fopen (KeyFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe paquete", 3);
		return;
	}else{

		while(fgets(values[i], 141, fp) != NULL) 
		{
			for (j = 0; values[i][j] && isspace(values[i][j]); j++)
				;
			if (values[i][j] == '*' || values[i][j] == '\0')
				continue;
			i=i+1;
		}

		fclose(fp);
	
	}

	strcpy(date,__DATE__);
	strcat(date," ");
	strcat(date,__TIME__);
	strcat(date, "\n");

	strcpy(str5, "Num. descargas: ");
	memmove(downloads, downloads+10, strlen(downloads));
	strcat(str5, downloads);

	strcpy(printBuf, "Cargador de llaves\nMenu Admin\nEstatus Llaves\n*******Config*******\nImpresion\n");
	strcat(printBuf, date);
	strcat(printBuf, "S/N:000185237789\n");
	strcat(printBuf,"Max.descargas:20000\n");
	strcat(printBuf, str5);
	strcat(printBuf, "\n");
	strcat(printBuf, packName);
	strcat(printBuf, "\n");

	for(g=0;g<=200;g++){

			if(strcmp(keysLong, "keysLong=32\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][113]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+105, strlen(valuesCopy[g]));

				strcat(printBuf, "BDK KCV:");
				strcat(printBuf, valuesCopy[g]);
				strcat(printBuf, "\nKSI:");
				strcat(printBuf, values[g]);
				strcat(printBuf, "\n");
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][112]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+106, strlen(valuesCopy[g]));

				strcpy(printBuf2, "KIN:");
				strcat(printBuf2, values[g]);
				strcat(printBuf2, "\nKCV:");
				strcat(printBuf2, valuesCopy[g]);
				strcat(printBuf2, "\n");
				strcat(printBuf, printBuf2);

			}
		}

			if(strcmp(keysLong, "keysLong=48\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][129]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+121, strlen(valuesCopy[g]));

				strcat(printBuf, "BDK KCV:");
				strcat(printBuf, valuesCopy[g]);
				strcat(printBuf, "\nKSI:");
				strcat(printBuf, values[g]);
				strcat(printBuf, "\n");
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][128]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+122, strlen(valuesCopy[g]));

				strcpy(printBuf2, "KIN:");
				strcat(printBuf2, values[g]);
				strcat(printBuf2, "\nKCV:");
				strcat(printBuf2, valuesCopy[g]);
				strcat(printBuf2, "\n");
				strcat(printBuf, printBuf2);
			}
		}
	}

		PrnClrBuff_Api();

		PrnStr_Api(printBuf);

		PrnStart_Api();


}

  int InputPacketPhysicalGetInfo(void)
{
	char Tempbuf[10],KeyFileName[100];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));
		strcpy(KeyFileName, "‪");
		strcat(KeyFileName, "‪/mtd0/dll/");
		strcat(KeyFileName, Tempbuf);
		strcat(KeyFileName, ".xml");

		while(KeyFileName[0]!='/'){

			memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

		}
		if(KeyFileName[0]=='/'){
			printPhysicalStatus(KeyFileName);
		}
		
	}
}


int printPhysicalUserStatus(char values[][64], u8 ucTimeOut)
{
	int g=1, k=0, j=0, h=0, i=0;
	char valuesCopy[200][23], date[30], printBuf[20000], str[4], str2[15], str3[4], str4[20];

	strcpy(date,__DATE__);
	strcat(date," ");
	strcat(date,__TIME__);
	strcat(date,"\n");

	for(g=0;g<=200;g++){

		if(strstr(values[g],"true")){
			values[g][15]='\0';
			memmove(values[g], values[g]+7, strlen(values[g]));
			strcpy(valuesCopy[g], values[g]);
			strcat(valuesCopy[g], " Activo");
			valuesCopy[g][23]='\0';
			}
				
		if(strstr(values[g],"false")){
			values[g][15]='\0';
			memmove(values[g], values[g]+7, strlen(values[g]));
			strcpy(valuesCopy[g], values[g]);
			strcat(valuesCopy[g], " Bloq");
			valuesCopy[g][23]='\0';
		}

	}

	strcpy(printBuf, "Cargador de llaves\nMenu Admin\nEstatus Usuarios\n*******Usuario*******\n");
	strcat(printBuf, date);

	while(strstr(valuesCopy[i], "id")!=NULL){
		strcat(printBuf, valuesCopy[i]);
		strcat(printBuf, "\n");
		i++;
	}

	for(h=0;h<=200;h++){

		if(strstr(valuesCopy[h],"Activo")!=NULL){
			k=k+1;
		}
				
		if(strstr(valuesCopy[h],"id")!=NULL){
			j=j+1;
		}

	}

	sprintf(str, "%d", j);
	strcpy(str2, "USUARIOS: ");
	strcat(str2, str);

	sprintf(str3, "%d", k);
	strcpy(str4, "DISPONIBLES: ");
	strcat(str4, str3);

	strcat(printBuf, str2);
	strcat(printBuf, "\n");
	strcat(printBuf, str4);
	strcat(printBuf, "\n");

	PrnClrBuff_Api();

	PrnStr_Api(printBuf);
	
	PrnStart_Api();
}

int findPhysicalValues(char *UserFileName){

	FILE *fp;
	int i=0, j=0;
	char values[200][64];

	fp = fopen (UserFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existen usuarios2", 3);
		return -2;
	}

	while(fgets(values[i], 64, fp) != NULL) 
	{
		for (j = 0; values[i][j] && isspace(values[i][j]); j++)
			;
		if (values[i][j] == '*' || values[i][j] == '\0')
			continue;
        i++;
    }

	fclose(fp);

	printPhysicalUserStatus(values, 60);

}

int displayUsers(char values[][23]){

	int i=0,j=0, k=0, g=0;
	char str[4], str2[15], str3[4], str4[20];

	for(g=0;g<=200;g++){

		if(strstr(values[g],"Activo")!=NULL){
			k=k+1;
		}
				
		if(strstr(values[g],"id")!=NULL){
			j=j+1;
		}

	}

	while(WaitAnyKey_Api(60)!=ESC && i<=200){

		ScrClrLine_Api(LINE2, LINE6);

		ScrDisp_Api(LINE2, 0, values[i], FDISP|LDISP);

		KBFlush_Api();


		if(strstr(values[i], "ÌÌÌÌÌÌÌÌÌÌ") != NULL || strstr(values[i],"id")==NULL){


			sprintf(str, "%d", j);
			strcpy(str2, "USUARIOS: ");
			strcat(str2, str);

			sprintf(str3, "%d", k);
			strcpy(str4, "DISPONIBLES: ");
			strcat(str4, str3);

			ScrClrLine_Api(LINE2, LINE6);
			ScrDisp_Api(LINE2, 0, str2, FDISP|LDISP);
			ScrDisp_Api(LINE3, 0, str4, FDISP|LDISP);
			ScrBrush_Api();

			KBFlush_Api();

			if(WaitAnyKey_Api(60)==ESC){
				return ESC;
			}
		}

		i=i+1;
	}
}

int printUserStatus(char values[][64], u8 ucTimeOut)
{
	int g=0;
	char valuesCopy[200][23];
	char date[30];

	strcpy(date,__DATE__);
	strcat(date," ");
	strcat(date,__TIME__);

	for(g=0;g<=200;g++){

		if(strstr(values[g],"true")){
			values[g][15]='\0';
			memmove(values[g], values[g]+7, strlen(values[g]));
			strcpy(valuesCopy[g], values[g]);
			strcat(valuesCopy[g], " Activo");
			valuesCopy[g][22]='\0';
			}
				
		if(strstr(values[g],"false")){
			values[g][15]='\0';
			memmove(values[g], values[g]+7, strlen(values[g]));
			strcpy(valuesCopy[g], values[g]);
			strcat(valuesCopy[g], " Bloq");
			valuesCopy[g][22]='\0';
		}

	}

	KBFlush_Api();

	while(1)
	{	

	DispTitle("Cargador de llaves");

	ScrClrLine_Api(LINE2, LINE6);

	ScrDisp_Api(LINE2, 0, "Menu Admin", FDISP|CDISP);
	ScrDisp_Api(LINE3, 0, "Estatus Usuarios", FDISP|CDISP);
	ScrDisp_Api(LINE4, 0, "*******Usuario*******", FDISP|CDISP);
	ScrDisp_Api(LINE5, 0, date, FDISP|CDISP);
	ScrBrush_Api();

	KBFlush_Api();

		if(WaitAnyKey_Api(ucTimeOut)){
			displayUsers(valuesCopy);
		}
		if(WaitAnyKey_Api(60)==ESC){
			return ESC;
		}

}
	return 0;
}

int findValues(char *UserFileName){

	FILE *fp;
	int i=0, j=0;
	char values[200][64];

	fp = fopen (UserFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existen usuarios1", 3);
		return -2;
	}

	while(fgets(values[i], 64, fp) != NULL) 
	{
		for (j = 0; values[i][j] && isspace(values[i][j]); j++)
			;
		if (values[i][j] == '*' || values[i][j] == '\0')
			continue;
        i++;
    }

	fclose(fp);

	printUserStatus(values, 60);

}


int InputPacketNumber(unsigned char *PacketNumber)
{
	int ret=0;
	char Tempbuf[32] ;
	
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Ingrese id llave:", FDISP|LDISP|INCOL);
	ret = GetScanf(MMI_NUMBER, 4, 10, Tempbuf, 30, LINE4 , LINE4 ,16);
	if(ret == ENTER )
		memcpy(PacketNumber, Tempbuf+1, 10);
	else 
		return ret;	
	
	return OK;	
}

int displayPacket(char values[][141],char values2[][141], char *KeyFileName, char *packName, char *packNumber, char *amountComp, char *keysLong){

	int i=3, j=4;
	char temp[80];
	while(WaitAnyKey_Api(60)!=ESC && i<=200){

		if(!strstr(values[i],"ÌÌÌÌÌÌÌÌÌÌÌ")){
			if(strstr(values[i],"BDK")){

				strcpy(temp,values[i]);

				temp[16]=0;

				ScrClrLine_Api(LINE2, LINE6);
				ScrDisp_Api(LINE2, 0, packName, FDISP|LDISP);
				ScrDisp_Api(LINE3, 0, temp, FDISP|LDISP);

				memmove(values[i], values[i]+18, strlen(values[i]));
				ScrDisp_Api(LINE4, 0, values[i], FDISP|LDISP);
				

			}
		}

		if(strstr(values[i],"ÌÌÌÌÌÌÌÌÌÌÌ")||!strstr(values[i],"BDK")){
		
			ScrDisp_Api(LINE2, 0, packName, FDISP|LDISP);
			while(WaitAnyKey_Api(60)!=ESC && j<=200){

			if(!strstr(values2[j],"ÌÌÌÌÌÌÌÌÌÌÌ") ){
				if(strstr(values2[j],"KIN")){

					strcpy(temp,values2[j]);

					temp[9]=0;

					ScrClrLine_Api(LINE2, LINE6);
					ScrDisp_Api(LINE2, 0, temp, FDISP|LDISP);

					memmove(values2[j], values2[j]+9, strlen(values2[j]));
					ScrDisp_Api(LINE3, 0, values2[j], FDISP|LDISP);

				}

			}
			
				if(strstr(values2[j],"ÌÌÌÌÌÌÌÌÌÌÌ")||!strstr(values2[i],"KIN")){
						
					if(WaitAnyKey_Api(60)==ESC){
							return ESC;
					}
				}

			ScrBrush_Api();
			KBFlush_Api();
			j=j+1;
			}
		}
	
		ScrBrush_Api();
		KBFlush_Api();

		i=i+1;
	}

}

int printPackStatus(char values[][141], char *KeyFileName, char *packName, char *packNumber, char *amountComp, char *keysLong)
{
	int g=0;
	char date[30];
	char valuesCopy[200][141];
	char valuesFinalCopy[200][141];
	char valuesFinalCopy2[200][141];

	strcpy(date,__DATE__);
	strcat(date," ");
	strcat(date,__TIME__);

	for(g=0;g<=200;g++){

if(strcmp(keysLong, "keysLong=32\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][114]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+105, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy[g], "BDK KCV:");
				strcat(valuesFinalCopy[g], valuesCopy[g]);
				strcat(valuesFinalCopy[g], " KSI:");
				strcat(valuesFinalCopy[g], values[g]);
				valuesFinalCopy[g][40]='\0';
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][112]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+106, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy2[g], "KIN:");
				strcat(valuesFinalCopy2[g], values[g]);
				strcat(valuesFinalCopy2[g], " KCV:");
				strcat(valuesFinalCopy2[g], valuesCopy[g]);
				valuesFinalCopy2[g][30]='\0';
			}
		}

		if(strcmp(keysLong, "keysLong=48\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][130]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+121, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy[g], "BDK KCV:");
				strcat(valuesFinalCopy[g], valuesCopy[g]);
				strcat(valuesFinalCopy[g], " KSI:");
				strcat(valuesFinalCopy[g], values[g]);
				valuesFinalCopy[g][40]='\0';
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][128]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+122, strlen(valuesCopy[g]));

				strcpy(valuesFinalCopy2[g], "KIN:");
				strcat(valuesFinalCopy2[g], values[g]);
				strcat(valuesFinalCopy2[g], " KCV:");
				strcat(valuesFinalCopy2[g], valuesCopy[g]);
				valuesFinalCopy2[g][40]='\0';
			}
		}


	}

	KBFlush_Api();
	while(1)
	{	

	DispTitle("Cargador de llaves");

	ScrClrLine_Api(LINE2, LINE6);

	ScrDisp_Api(LINE2, 0, "Menu Admin", FDISP|CDISP);
	ScrDisp_Api(LINE3, 0, "Estatus Paquetes", FDISP|CDISP);
	ScrDisp_Api(LINE4, 0, "*******Usuario*******", FDISP|CDISP);
	ScrDisp_Api(LINE5, 0, date, FDISP|CDISP);
	ScrBrush_Api();

	KBFlush_Api();

		if(WaitAnyKey_Api(60)==ENTER){
		displayPacket(valuesFinalCopy, valuesFinalCopy2, KeyFileName, packName, packNumber, amountComp, keysLong);
		}
		if(WaitAnyKey_Api(60)==ESC){
			return ESC;
		}

}
	return 0;
}

  int findPackValues(char *KeyFileName){

	FILE *fp;
	int i=0, j=0;
	char values[200][141], packFileText [200];
	char trash[20],downloads[20], packName[20], packNumber[20], amountComp[20], keysLong[20];

	fp = fopen (KeyFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe paquete", 3);
		return;
	}
	else{
		fgets(packFileText, 100, fp); fclose(fp);
	}

	strcpy(trash, strtok(packFileText , " "));
	strcpy(downloads, strtok(NULL , " "));
    strcpy(packName, strtok(NULL , " "));
	strcpy(packNumber, strtok(NULL, " "));
	strcpy(amountComp , strtok(NULL, " "));
	strcpy(keysLong, strtok(NULL, " "));

	fp = fopen (KeyFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe paquete", 3);
		return;
	}

	while(fgets(values[i], 141, fp) != NULL) 
	{
		for (j = 0; values[i][j] && isspace(values[i][j]); j++)
			;
		if (values[i][j] == '*' || values[i][j] == '\0')
			continue;
        i++;
    }

	if(fp!=NULL){
		fclose(fp);
	}
	printPackStatus(values, KeyFileName, packName, packNumber, amountComp, keysLong);

}

  int InputPacketGetInfo(void)
{
	char Tempbuf[10],KeyFileName[100];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));
		strcpy(KeyFileName, "");
		strcat(KeyFileName, "/mtd0/dll/");
		strcat(KeyFileName, Tempbuf);
		strcat(KeyFileName, ".xml");

		while(KeyFileName[0]!='/'){

			memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

		}
		if(KeyFileName[0]=='/'){
			findPackValues(KeyFileName);
		}

	}
}



int printPacketPhysicalStatus(char *KeyFileName){

	FILE *fp;
	int i=0, j=0, g=0;
	char date[30];
	char str[30], str3[30], str5[40], printBuf[20000], printBuf2[20000], packFileText[200],trash[20],downloads[20], packName[20],packNumber[20], amountComp[20], keysLong[20], values[200][141],valuesCopy[200][141], valuesFinalCopy[200][141], valuesFinalCopy2[200][141];

	fp = fopen (KeyFileName, "r"); 
	
	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe paquete", 3);
		return;
	}else{
	fgets (packFileText, 100, fp); fclose(fp);
	}

	strcpy(trash, strtok(packFileText , " "));
	strcpy(downloads, strtok(NULL , " "));
	strcpy(packName, strtok(NULL , " "));
	strcpy(packNumber, strtok(NULL , " "));
	strcpy(amountComp, strtok(NULL , " "));
	strcpy(keysLong, strtok(NULL , " "));

	fp = fopen (KeyFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe paquete", 3);
		return;
	}

	while(fgets(values[i], 141, fp) != NULL) 
	{
		for (j = 0; values[i][j] && isspace(values[i][j]); j++)
			;
		if (values[i][j] == '*' || values[i][j] == '\0')
			continue;
        i++;
    }
	if(fp!=NULL){
		fclose(fp);
	}

	strcpy(date,__DATE__);
	strcat(date," ");
	strcat(date,__TIME__);
	strcat(date, "\n");


	strcpy(printBuf, "Cargador de llaves\nMenu Admin\nEstatus Paquetes\n*******Usuario*******\n");
	strcat(printBuf, date);
	strcat(printBuf, packName);
	strcat(printBuf, "\n");

	for(g=0;g<=200;g++){

			if(strcmp(keysLong, "keysLong=32\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][113]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+105, strlen(valuesCopy[g]));

				strcat(printBuf, "BDK KCV:");
				strcat(printBuf, valuesCopy[g]);
				strcat(printBuf, "\nKSI:");
				strcat(printBuf, values[g]);
				strcat(printBuf, "\n");
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][112]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+106, strlen(valuesCopy[g]));

				strcpy(printBuf2, "KIN:");
				strcat(printBuf2, values[g]);
				strcat(printBuf2, "\nKCV:");
				strcat(printBuf2, valuesCopy[g]);
				strcat(printBuf2, "\n");
				strcat(printBuf, printBuf2);

			}
		}

			if(strcmp(keysLong, "keysLong=48\n")==0){

			if(strstr(values[g],"type=\"BDK\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][27]='\0';
				memmove(values[g], values[g]+15, strlen(values[g]));

				valuesCopy[g][129]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+121, strlen(valuesCopy[g]));

				strcat(printBuf, "BDK KCV:");
				strcat(printBuf, valuesCopy[g]);
				strcat(printBuf, "\nKSI:");
				strcat(printBuf, values[g]);
				strcat(printBuf, "\n");
			}

			if(strstr(values[g],"type=\"EFT\"")){

				strcpy(valuesCopy[g], values[g]);

				values[g][20]='\0';
				memmove(values[g], values[g]+16, strlen(values[g]));

				valuesCopy[g][128]='\0';
				memmove(valuesCopy[g], valuesCopy[g]+122, strlen(valuesCopy[g]));

				strcpy(printBuf2, "KIN:");
				strcat(printBuf2, values[g]);
				strcat(printBuf2, "\nKCV:");
				strcat(printBuf2, valuesCopy[g]);
				strcat(printBuf2, "\n");
				strcat(printBuf, printBuf2);
			}
		}
	}

		PrnClrBuff_Api();

		PrnStr_Api(printBuf);

		PrnStart_Api();


}

  int InputPacketInfoPhysical(void)
{
	char Tempbuf[10],KeyFileName[100];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));
		strcpy(KeyFileName, "");
		strcat(KeyFileName, "/mtd0/dll/");
		strcat(KeyFileName, Tempbuf);
		strcat(KeyFileName, ".xml");

		while(KeyFileName[0]!='/'){

			memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

		}
		if(KeyFileName[0]=='/'){
			printPacketPhysicalStatus(KeyFileName);
		}

	}
}

    int InputKeyComponentInfo(char* Tempbuf, char* Tempbuf2, char *KeyFileName){

	char Tempbuf3[50], Tempbuf4[50], Tempbuf5[50], Tempbuf6[50], Tempbuf7[50], Tempbuf8[50], Tempbuf9[50], Tempbuf10[50];
	FILE *fileStream; char packFileText [200];

	memset(Tempbuf3 , 0 , sizeof(Tempbuf3));
	memset(Tempbuf4 , 0 , sizeof(Tempbuf4));		
	memset(Tempbuf5 , 0 , sizeof(Tempbuf5));
	memset(Tempbuf6 , 0 , sizeof(Tempbuf6));
	memset(Tempbuf7 , 0 , sizeof(Tempbuf7));
	memset(Tempbuf8 , 0 , sizeof(Tempbuf8));
	memset(Tempbuf9 , 0 , sizeof(Tempbuf9));
	memset(Tempbuf10 , 0 , sizeof(Tempbuf10));

	memmove(Tempbuf2, Tempbuf2+1, strlen(Tempbuf2));

	fileStream = fopen (KeyFileName, "r"); fgets (packFileText, 100, fileStream); fclose(fileStream);

	if(strstr(packFileText, "amountComp=2") != NULL) {

		if(strstr(packFileText, "keysLong=32") != NULL) {

			if(strcmp(Tempbuf2, "1")==0){

				ScrClrLine_Api(LINE2, LINE5);
				ScrDisp_Api(LINE2 , 0 , "KSI:", FDISP|LDISP|INCOL);
				memset(Tempbuf3 , 0 , sizeof(Tempbuf3));

				if(GetScanf(MMI_LETTER, 10, 10, Tempbuf3, 30, LINE4 , LINE4 ,16)== ENTER ){

					memmove(Tempbuf3, Tempbuf3+1, strlen(Tempbuf3));

					KekSet2_32(KeyFileName, Tempbuf2, Tempbuf3);
					}
				}

			if(strcmp(Tempbuf2, "2")==0){
					
				ScrClrLine_Api(LINE2, LINE5);
				ScrDisp_Api(LINE2 , 0 , "KIN:", FDISP|LDISP|INCOL);
				memset(Tempbuf3 , 0 , sizeof(Tempbuf3));

							if(GetScanf(MMI_LETTER, 4, 4, Tempbuf3, 30, LINE4 , LINE4 ,16)== ENTER ){
								memmove(Tempbuf3, Tempbuf3+1, strlen(Tempbuf3));
								strcat(Tempbuf3, "000000");
								
								KekSet2_32(KeyFileName, Tempbuf2, Tempbuf3);
								}
							}
						
					}// FINAL 2 COMPONENTES 32 LONG

		if(strstr(packFileText, "keysLong=48") != NULL) {

			if(strcmp(Tempbuf2, "1")==0){
					
				ScrClrLine_Api(LINE2, LINE5);
				ScrDisp_Api(LINE2 , 0 , "KSI:", FDISP|LDISP|INCOL);
				memset(Tempbuf3 , 0 , sizeof(Tempbuf3));

							if(GetScanf(MMI_LETTER, 10, 10, Tempbuf3, 30, LINE4 , LINE4 ,16)== ENTER ){
								memmove(Tempbuf3, Tempbuf3+1, strlen(Tempbuf3));

								KekSet2_48(KeyFileName, Tempbuf2, Tempbuf3);

							}
						}
					

					if(strcmp(Tempbuf2, "2")==0){
					
							ScrClrLine_Api(LINE2, LINE5);
							ScrDisp_Api(LINE2 , 0 , "KIN:", FDISP|LDISP|INCOL);
							memset(Tempbuf3 , 0 , sizeof(Tempbuf3));

							if(GetScanf(MMI_LETTER, 4, 4, Tempbuf3, 30, LINE4 , LINE4 ,16)== ENTER ){
								memmove(Tempbuf3, Tempbuf3+1, strlen(Tempbuf3));
								strcat(Tempbuf3, "000000");

								KekSet2_48(KeyFileName, Tempbuf2, Tempbuf3);
								}
							}
						}//FINAL 2 COMPONENTES 48 LONG
					}//FINAL DOS COMPONENTES

			if(strstr(packFileText, "amountComp=3") != NULL) {

				if(strstr(packFileText, "keysLong=32") != NULL) {

					if(strcmp(Tempbuf2, "1")==0){
					
							ScrClrLine_Api(LINE2, LINE5);
							ScrDisp_Api(LINE2 , 0 , "KSI:", FDISP|LDISP|INCOL);
							memset(Tempbuf3 , 0 , sizeof(Tempbuf3));

							if(GetScanf(MMI_LETTER, 10, 10, Tempbuf3, 30, LINE4 , LINE4 ,16)== ENTER ){
								memmove(Tempbuf3, Tempbuf3+1, strlen(Tempbuf3));
								KekSet3_32(KeyFileName, Tempbuf2, Tempbuf3);
								}
							}

					if(strcmp(Tempbuf2, "2")==0){
					
							ScrClrLine_Api(LINE2, LINE5);
							ScrDisp_Api(LINE2 , 0 , "KIN:", FDISP|LDISP|INCOL);
							memset(Tempbuf3 , 0 , sizeof(Tempbuf3));

							if(GetScanf(MMI_LETTER, 4, 4, Tempbuf3, 30, LINE4 , LINE4 ,16)== ENTER ){
								memmove(Tempbuf3, Tempbuf3+1, strlen(Tempbuf3));
								strcat(Tempbuf3, "000000");

								KekSet3_32(KeyFileName, Tempbuf2, Tempbuf3);
									}
								}
							
						}//FINAL 3 COMPONENTES LONGITUD 32

				if(strstr(packFileText, "keysLong=48") != NULL) {

					if(strcmp(Tempbuf2, "1")==0){
					
							ScrClrLine_Api(LINE2, LINE5);
							ScrDisp_Api(LINE2 , 0 , "KSI:", FDISP|LDISP|INCOL);
							memset(Tempbuf3 , 0 , sizeof(Tempbuf3));

							if(GetScanf(MMI_LETTER, 10, 10, Tempbuf3, 30, LINE4 , LINE4 ,16)== ENTER ){
								memmove(Tempbuf3, Tempbuf3+1, strlen(Tempbuf3));
								KekSet3_48(KeyFileName, Tempbuf2, Tempbuf3);

									}
								}
							

						if(strcmp(Tempbuf2, "2")==0){
					
							ScrClrLine_Api(LINE2, LINE5);
							ScrDisp_Api(LINE2 , 0 , "KIN:", FDISP|LDISP|INCOL);
							memset(Tempbuf3 , 0 , sizeof(Tempbuf3));

							if(GetScanf(MMI_LETTER, 4, 4, Tempbuf3, 30, LINE4 , LINE4 ,16)== ENTER ){
								memmove(Tempbuf3, Tempbuf3+1, strlen(Tempbuf3));
								strcat(Tempbuf3, "000000");

								KekSet3_48(KeyFileName, Tempbuf2, Tempbuf3);
							}
						}	
							
				}//FINAL 3 COMPONENTES 48 LONG
			}//FINAL 3 COMPONENTES
		}

  
 int InputKeyTypeInfo(char* Tempbuf, char *KeyFileName){

    char Tempbuf2[50];

	memset(Tempbuf2 , 0 , sizeof(Tempbuf2));

		ScrClrLine_Api(LINE2, LINE5);
		ScrDisp_Api(LINE2 , 0 , "Tipo llave:", FDISP|LDISP|INCOL);
		ScrDisp_Api(LINE3 , 0 , "1=BDK, 2=EFTsec", FDISP|LDISP|INCOL);
		memset(Tempbuf2 , 0 , sizeof(Tempbuf2));
		
		if(GetScanf(MMI_NUMBER, 1, 1, Tempbuf2, 30, LINE4 , LINE4 ,16)== ENTER ){
			
			InputKeyComponentInfo(Tempbuf,Tempbuf2, KeyFileName);
		}
 }


 int InputKeyInfo(void)
{
	int KeyFileLen=0;
	char Tempbuf[50];
	char KeyFileName[100];

	memset(Tempbuf , 0 , sizeof(Tempbuf)); // Nombre del paquete

	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre de paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));

		strcpy(KeyFileName, "");
		strcat(KeyFileName, "/mtd0/dll/");
		strcat(KeyFileName, Tempbuf);
		strcat(KeyFileName, ".xml");

		while(KeyFileName[0]!='/'){

			memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

		}
		if(KeyFileName[0]=='/'){
		
			if (KeyFileName == NULL)
				return -1;

			KeyFileLen = GetFileSize_Api((const char *)KeyFileName);

			if (KeyFileLen == 0)
			{
				ScrClrLine_Api(LINE2, LINE6);
				ErrorPrompt(KeyFileName, 3);
				return -2;

			}else{
				InputKeyTypeInfo(Tempbuf,KeyFileName);
			}
		}


	}
 }

  int findUser(char *UserFileName, char *title, char *whereToGo){

	FILE *fp;
	int i=0,j=0;
	char values[200][70];

	fp = fopen (UserFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existen usuarios 3", 3);
		return -2;
	}
		
	while(fgets(values[i], 64, fp) != NULL){

		if(strstr(values[i], title)!=NULL){

		  if(strcmp(whereToGo, "AD")==0){
			WriteFile_Api(USER_LOGGED_FILE_IN, (unsigned char*)title, 0, strlen(title));
			adminMenu();
		  }
		  if(strcmp(whereToGo, "OP")==0){
			WriteFile_Api(USER_LOGGED_FILE_IN, (unsigned char*)title, 0, strlen(title));
			operatorMenu();
		  }
		}
		else{
			i++;
		}
 }
 
	fclose(fp);


}

 int login(char *UserFileName, char *str, char *str2, char *userType){

	int UserFileLen=0;
	char *pUserFile=NULL;
	USER_FILE_STR myUser;

	memmove(str, str+1, strlen(str));
	memmove(str2, str2+1, strlen(str2));

	strcpy(myUser.user_id, "{ user_id="); 
	strcat(myUser.user_id, (char *)str);
	strcpy(myUser.user_password, " user_password="); 
	strcat(myUser.user_password, (char *)str2);
	strcpy(myUser.user_type, " user_type="); 
	strcat(myUser.user_type, userType);
	strcpy(myUser.isActive, " isActive=true }"); 

	strcat(myUser.user_id, myUser.user_password);
	strcat(myUser.user_id, myUser.user_type);
	strcat(myUser.user_id, myUser.isActive);

		if (UserFileName == NULL)
		return -1;
	
		UserFileLen = GetFileSize_Api(UserFileName);
		
		pUserFile = (char *)malloc(UserFileLen+1);
		
		if (pUserFile == NULL)
		return -3;

		findUser(USER_FILE_IN, myUser.user_id, userType);
}

 int InputUserLoginInfo(char *userType)
{
	char Tempbuf[20], Tempbuf2[20];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	memset(Tempbuf2 , 0 , sizeof(Tempbuf2));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Ingrese usuario:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		ScrClrLine_Api(LINE2, LINE5);
		ScrDisp_Api(LINE2 , 0 , "Ingrese clave:", FDISP|LDISP|INCOL);
		memset(Tempbuf2 , 0 , sizeof(Tempbuf2));

		if(GetScanf(MMI_LETTER, 4, 4, Tempbuf2, 30, LINE4 , LINE4 ,16)== ENTER ){
			login(USER_FILE_IN, Tempbuf,Tempbuf2, userType);
		}
	}
}

  int findUser4(char *UserFileName, char *title){

	FILE *fp;
	int i=0,j=0;
	char values[200][70];

	fp = fopen (UserFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existen usuarios 3", 3);
		return -2;
	}
		
	while(fgets(values[i], 64, fp) != NULL){

		if(strstr(values[i], title)!=NULL){
			return 6;
		}
		else{
			i++;
		}
 }
 
	fclose(fp);

}

  int findUser3(char *UserFileName, char *title){

	FILE *fp;
	int i=0,j=0;
	char values[200][70];

	fp = fopen (UserFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existen usuarios 3", 3);
		return -2;
	}
		
	while(fgets(values[i], 64, fp) != NULL){

		if(strstr(values[i], title)!=NULL){
			return 5;
		}
		else{
			i++;
		}
 }
 
	fclose(fp);

}

   int findUser2(char *UserFileName, char *title){

	FILE *fp;
	int i=0,j=0;
	char values[200][70];

	fp = fopen (UserFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existen usuarios 3", 3);
		return -2;
	}
		
	while(fgets(values[i], 64, fp) != NULL){

		if(strstr(values[i], title)!=NULL){

			if(findUser3(USER_LOGGED_FILE_IN, title)==5){
				return 5;

			} else{
			return 9;
			}
		}
		else{
			i++;
		}
 }
 
	fclose(fp);

}

 int login2(char *UserFileName, char *str, char *str2, char *userType){

	int UserFileLen=0;
	char *pUserFile=NULL;
	USER_FILE_STR myUser;

	memmove(str, str+1, strlen(str));
	memmove(str2, str2+1, strlen(str2));

	strcpy(myUser.user_id, "{ user_id="); 
	strcat(myUser.user_id, (char *)str);
	strcpy(myUser.user_password, " user_password="); 
	strcat(myUser.user_password, (char *)str2);
	strcpy(myUser.user_type, " user_type="); 
	strcat(myUser.user_type, userType);
	strcpy(myUser.isActive, " isActive=true }"); 

	strcat(myUser.user_id, myUser.user_password);
	strcat(myUser.user_id, myUser.user_type);
	strcat(myUser.user_id, myUser.isActive);

		if (UserFileName == NULL)
		return -1;
	
		UserFileLen = GetFileSize_Api(UserFileName);
		
		pUserFile = (char *)malloc(UserFileLen+1);
		
		if (pUserFile == NULL)
		return -3;

		if(findUser2(USER_FILE_IN, myUser.user_id)==9){
			return 9;
		}
		if(findUser2(USER_FILE_IN, myUser.user_id)==5){
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("User repetido", 3);
			return 5;
		}
}


  int InputUserLoginInfo2(char *userType)
{
	char Tempbuf[20], Tempbuf2[20];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	memset(Tempbuf2 , 0 , sizeof(Tempbuf2));

	if(findUser4(USER_LOGGED_FILE_IN, "doubleVerSu")==6){
		return 9;
	}
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Ingrese usuario:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		ScrClrLine_Api(LINE2, LINE5);
		ScrDisp_Api(LINE2 , 0 , "Ingrese clave:", FDISP|LDISP|INCOL);
		memset(Tempbuf2 , 0 , sizeof(Tempbuf2));

		if(GetScanf(MMI_LETTER, 4, 4, Tempbuf2, 30, LINE4 , LINE4 ,16)== ENTER ){

			if(login2(USER_FILE_IN, Tempbuf,Tempbuf2, userType)==9){
				WriteFile_Api(USER_LOGGED_FILE_IN, (unsigned char*)"doubleVerSu", 68, strlen("doubleVerSu"));
				return 9;
			}else{
				return;
			}
		}

	if(WaitEnterAndEscKey_Api(30)==ESC){
		return ESC;
	}
	}



}


void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}


 int InputPacketInfo(void)
{
	char Tempbuf[10], Tempbuf2[10], Tempbuf3[10], Tempbuf4[10], KeyFileName[100];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	memset(Tempbuf2 , 0 , sizeof(Tempbuf2));
	memset(Tempbuf3 , 0 , sizeof(Tempbuf3));
	memset(Tempbuf4 , 0 , sizeof(Tempbuf4));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre de paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 1, 8, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		ScrClrLine_Api(LINE2, LINE5);
		ScrDisp_Api(LINE2 , 0 , "Numero paquete", FDISP|LDISP|INCOL);
		memset(Tempbuf2 , 0 , sizeof(Tempbuf2));

		if(GetScanf(MMI_NUMBER, 7, 7, Tempbuf2, 30, LINE4 , LINE4 ,16)== ENTER ){
			
			ScrClrLine_Api(LINE2, LINE5);
			ScrDisp_Api(LINE2 , 0 , "Cantidad Componentes:", FDISP|LDISP|INCOL);
			memset(Tempbuf3 , 0 , sizeof(Tempbuf3));
			
			if(GetScanf(MMI_LETTER, 1, 1, Tempbuf3, 30, LINE4 , LINE4 ,16)== ENTER ){

				ScrClrLine_Api(LINE2, LINE5);
				ScrDisp_Api(LINE2 , 0 , "Long. de la llave 32/48:", FDISP|LDISP|INCOL);
				memset(Tempbuf4 , 0 , sizeof(Tempbuf4));

				if(GetScanf(MMI_NUMBER, 2, 3, Tempbuf4, 30, LINE4 , LINE4 ,16)== ENTER ){
					
					memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));
					strcpy(KeyFileName, "");
					strcat(KeyFileName, "/mtd0/dll/");
					strcat(KeyFileName, Tempbuf);
					strcat(KeyFileName, ".xml");

				while(KeyFileName[0]!='/'){

					memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

				}
				if(KeyFileName[0]=='/'){
					createPack(KeyFileName, Tempbuf,Tempbuf2, Tempbuf3, Tempbuf4 );
				}

			}
		}
	}
}
 }


 int createPack(char *result, char* packName, char* packNumber, char* amountComp, char* keysLong){

	 char toWrite[300];
	 FILE *fp;

	 memmove(packNumber, packNumber+1, strlen(packNumber));
	 memmove(amountComp, amountComp+1, strlen(amountComp));
	 memmove(keysLong, keysLong+1, strlen(keysLong));

	 fp = fopen ((const char *)result, "r");

	 strcpy(toWrite, "//");
	 strcat(toWrite, " downloads=0 ");
	 strcat(toWrite, "packName=");
	 strcat(toWrite, packName);
	 strcat(toWrite, " ");
	 strcat(toWrite, "packNumber=");
	 strcat(toWrite, packNumber);
	 strcat(toWrite, " ");

	 if(strcmp(amountComp, "2")==0){
	 strcat(toWrite, "amountComp=");
	 strcat(toWrite, "2");
	 strcat(toWrite, " ");
	 }

	 if(strcmp(amountComp, "3")==0){
	 strcat(toWrite, "amountComp=");
	 strcat(toWrite, "3");
	 strcat(toWrite, " ");
	 }

	 strcat(toWrite, "keysLong=");
	 strcat(toWrite, keysLong);
	 strcat(toWrite, "\n");

	 if(fp==NULL && WriteFile_Api(result, (unsigned char*)toWrite, 0, strlen(toWrite))==0 && WriteFile_Api(result, (unsigned char*)"<?xml version=\"1.0\"  encoding=\"windows-1251\"?>\r\n<keyset>\r\n", strlen(toWrite), strlen("<?xml version=\"1.0\"  encoding=\"windows-1251\"?>\r\n<keyset>\r\n"))==0){	 
		
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("paquete creado", 3);

	 }
	 else if(fp!=NULL){

		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("paquete ya existe", 3);
		fclose(fp);
	 }
	 else{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt(result, 3);

	 }


 }

  int delPack(char* packName){

	 if(DelFile_Api(packName)==0){
		 ScrClrLine_Api(LINE2, LINE6);
		 ErrorPrompt("paquete borrado", 3);
	 }
	 //ReNameFile_Api("D:D:/work/KeyLoader/Debug/FileSystem/cdata/data/3.xml", "D:D:/work/KeyLoader/Debug/FileSystem/cdata/data/4.xml");
	 
 }

   int InputPacketDelInfo(void)
{
	char Tempbuf[10], KeyFileName[100];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

			 memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));
			 strcpy(KeyFileName, "");
					strcat(KeyFileName, "/mtd0/dll/");
					strcat(KeyFileName, Tempbuf);
					strcat(KeyFileName, ".xml");

				while(KeyFileName[0]!='/'){

					memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

				}
				if(KeyFileName[0]=='/'){
					delPack(KeyFileName);
				}

		}
}

  int delKey(char *KeyFileName, char *id){

	int KeyFileLen=0, ret=0, PacketTotalLen=0;
	char *pKeyFile=NULL, packFileText[100], newId[30];
	FILE *fp;

	if(strlen(id)==10){

	strcpy(newId, "number=\"");
	strcat(newId, id);
	strcat(newId, "\"");
	}

	if(strlen(id)==4){

	strcpy(newId, "number=\"");
	strcat(id, "000000");
	strcat(newId, id);
	strcat(newId, "\"");
	}

	fp = fopen (KeyFileName, "r"); 

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe paquete", 3);
		return -2;
	}else{
		fclose(fp);
	}

	if (KeyFileName == NULL)
		return -1;
	KeyFileLen = GetFileSize_Api(KeyFileName);
	if (KeyFileLen == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existen llaves", 3);
		return -2;
	}

	pKeyFile = (char *)malloc(KeyFileLen+1);

	if (pKeyFile == NULL)
		return -3;
	ret = ReadFile_Api(KeyFileName, pKeyFile, 0, &KeyFileLen);
	if (ret)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error lectura llaves", 3);
		return -4;
	}

	fp = fopen (KeyFileName, "r"); fgets (packFileText, 100, fp); fclose(fp);

	if(isSubstring(pKeyFile, newId)!=-1){

		if(strstr(packFileText, "amountComp=2") != NULL) {

			if(strstr(packFileText, "keysLong=32") != NULL) {

					PacketTotalLen = isSubstring(pKeyFile, newId);

					WriteFile_Api(KeyFileName, (unsigned char*)"                                                                                                                            ", PacketTotalLen-strlen("<packet "),strlen("                                                                                                                            "));

					ScrClrLine_Api(LINE2, LINE6);
					ErrorPrompt("llave borrada", 3);
				
			}
		}

		if(strstr(packFileText, "amountComp=3") != NULL) {

			if(strstr(packFileText, "keysLong=32") != NULL) {

					PacketTotalLen = isSubstring(pKeyFile, newId);

					WriteFile_Api(KeyFileName, (unsigned char*)"                                                                                                                            ", PacketTotalLen-strlen("<packet "),strlen("                                                                                                                            "));

					ScrClrLine_Api(LINE2, LINE6);
					ErrorPrompt("llave borrada", 3);
				
			}
		}

		if(strstr(packFileText, "amountComp=2") != NULL) {

			if(strstr(packFileText, "keysLong=48") != NULL) {


					PacketTotalLen = isSubstring(pKeyFile, newId);

					WriteFile_Api(KeyFileName, (unsigned char*)"                                                                                                                                            ", PacketTotalLen-strlen("<packet "),strlen("                                                                                                                                            "));

					ScrClrLine_Api(LINE2, LINE6);
					ErrorPrompt("llave borrada", 3);
			}
		}

		if(strstr(packFileText, "amountComp=3") != NULL) {

			if(strstr(packFileText, "keysLong=48") != NULL) {

					PacketTotalLen = isSubstring(pKeyFile, newId);

					WriteFile_Api(KeyFileName, (unsigned char*)"                                                                                                                                            ", PacketTotalLen-strlen("<packet "),strlen("                                                                                                                                            "));
					
					ScrClrLine_Api(LINE2, LINE6);
					ErrorPrompt("llave borrada", 3);
			}
		}
		}
		else{
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("no existe", 3);
		}
	
}

  int InputKeyDelInfo(void)
{
	char Tempbuf[10], Tempbuf2[15], KeyFileName[70];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	memset(Tempbuf2 , 0 , sizeof(Tempbuf2));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		ScrCls_Api();
		ScrClrLine_Api(LINE2, LINE6);
		ScrDisp_Api(LINE2 , 0 , "KSI O KIN:", FDISP|LDISP|INCOL);
		memset(Tempbuf2 , 0 , sizeof(Tempbuf2));

		if(GetScanf(MMI_LETTER, 4, 10, Tempbuf2, 30, LINE4 , LINE4 ,16)== ENTER ){

			memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));
			memmove(Tempbuf2, Tempbuf2+1, strlen(Tempbuf2));

			if(strlen(Tempbuf2)<5){
				strcat(Tempbuf2, "000000");
			}

			strcpy(KeyFileName, "");
			strcat(KeyFileName, "/mtd0/dll/");
			strcat(KeyFileName, Tempbuf);
			strcat(KeyFileName, ".xml");

			while(KeyFileName[0]!='/'){

				memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

			}
			if(KeyFileName[0]=='/'){
				delKey(KeyFileName, Tempbuf2);
			}

		}
	}
}

  int InputSaveUserInfo(char *userType)
{
	char Tempbuf[10], Tempbuf2[10];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	memset(Tempbuf2 , 0 , sizeof(Tempbuf2));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Id:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		ScrClrLine_Api(LINE2, LINE5);
		ScrDisp_Api(LINE2 , 0 , "Clave:", FDISP|LDISP|INCOL);
		memset(Tempbuf2 , 0 , sizeof(Tempbuf2));

		if(GetScanf(MMI_LETTER|MMI_PWD, 4, 4, Tempbuf2, 30, LINE4 , LINE4 ,16)== ENTER ){
			saveUser(USER_FILE_IN, Tempbuf,Tempbuf2, userType);
		}
	}
}

int saveUser(char *UserFileName, char *user_id, char *user_password, char *userType){

	int UserFileLen=0, ret=0, index=0;
	char *pUserFile=NULL;

	USER_FILE_STR myUser;

	memmove(user_id, user_id+1, strlen(user_id));
	memmove(user_password, user_password+1, strlen(user_password));

	if (UserFileName == NULL)
		return -1;
	UserFileLen = GetFileSize_Api(UserFileName);
	if (UserFileLen == 0)
	{
		strcpy(myUser.user_id, "{ user_id="); 
		strcat(myUser.user_id, (char *)user_id);
		strcpy(myUser.user_password, " user_password="); 
		strcat(myUser.user_password, (char *)user_password);
		strcpy(myUser.user_type, " user_type="); 
		strcat(myUser.user_type, userType);
		strcpy(myUser.isActive, " isActive=true }"); 

		strcat(myUser.user_id, myUser.user_password);
		strcat(myUser.user_id, myUser.user_type);
		strcat(myUser.user_id, myUser.isActive);
		WriteFile_Api(UserFileName, (unsigned char *)myUser.user_id, 0, strlen(myUser.user_id));

		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("usuario creado", 3);
	}

	pUserFile = (char *)malloc(UserFileLen+1);

	if(isSubstring(pUserFile, user_id)!=-1){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("usuario ya existe", 3);
		return -4;
	}
	if (pUserFile == NULL)
		return -3;
	ret = ReadFile_Api(UserFileName, pUserFile, 0, &UserFileLen);
	if (ret)
	{
		free(pUserFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error lectura usuarios", 3);
		return -4;
	}

	else
	{
		index = lastIndexOf(pUserFile, '}');
		strcpy(myUser.user_id, "\r");			
		
		strcat(myUser.user_id, "{ user_id="); 
		strcat(myUser.user_id, (char *)user_id);
		strcpy(myUser.user_password, " user_password="); 
		strcat(myUser.user_password, (char *)user_password);
		strcpy(myUser.user_type, " user_type="); 
		strcat(myUser.user_type, userType);
		strcpy(myUser.isActive, " isActive=true }"); 

		strcat(myUser.user_id, myUser.user_password);
		strcat(myUser.user_id, myUser.user_type);
		strcat(myUser.user_id, myUser.isActive);

		WriteFile_Api(UserFileName, (unsigned char *)myUser.user_id, index+1, strlen(myUser.user_id));
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("usuario creado", 3);

	}
}

int lastIndexOf(const char * str, const char toFind)
{
    int index = -1;
    int i = 0;

    while(str[i] != '\0')
    {
        // Update index if match is found
        if(str[i] == toFind)
        {
            index = i;
        }
        i++;
    }

    return index;
}

  int InputBlockUserInfo(void)
{
	char Tempbuf[10], Tempbuf2[10];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	memset(Tempbuf2 , 0 , sizeof(Tempbuf2));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Id:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		ScrClrLine_Api(LINE2, LINE5);
		ScrDisp_Api(LINE2 , 0 , "1=activar, 2=bloq:", FDISP|LDISP|INCOL);
		memset(Tempbuf2 , 0 , sizeof(Tempbuf2));

		if(GetScanf(MMI_NUMBER, 1, 1, Tempbuf2, 30, LINE4 , LINE4 ,16)== ENTER ){
			blUser(USER_FILE_IN, Tempbuf,Tempbuf2);
		}
	}
}

int blUser(char *UserFileName, char *user_id, char *isActive){

	int UserFileLen=0, ret=0, PacketTotalLen=0;
	char *pUserFile=NULL;

	memmove(user_id, user_id+1, strlen(user_id));
	memmove(isActive, isActive+1, strlen(isActive));

	if (UserFileName == NULL)
		return -1;
	UserFileLen = GetFileSize_Api(UserFileName);
	if (UserFileLen == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existen usuarios4", 3);
		return -2;
	}
	//×¼±¸¹¤×÷
	pUserFile = (char *)malloc(UserFileLen+1);
	if (pUserFile == NULL)
		return -3;
	ret = ReadFile_Api(UserFileName, pUserFile, 0, &UserFileLen);
	if (ret)
	{
		free(pUserFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error lectura usuarios", 3);
		return -4;
	}

	if( isSubstring(pUserFile, user_id)!=-1){

		PacketTotalLen = isSubstring(pUserFile, user_id);

		if(strcmp(isActive, "1")==0){
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("usuario act", 3);
			WriteFile_Api(UserFileName, (unsigned char*)"true } ", PacketTotalLen+46, strlen("true } "));
		}
		if(strcmp(isActive, "2")==0){
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("usuario bloq", 3);
			WriteFile_Api(UserFileName, (unsigned char*)"false }", PacketTotalLen+46, strlen("false }"));
		}

	}
	else{
			
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("usuario no existe", 3);
		return -4;
	}



	

}

  int InputChangePassword(void)
{
	char Tempbuf[10], Tempbuf3[10];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	memset(Tempbuf3 , 0 , sizeof(Tempbuf3));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Id:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){
		
			ScrClrLine_Api(LINE2, LINE5);
			ScrDisp_Api(LINE2 , 0 , "Clave:", FDISP|LDISP|INCOL);
			memset(Tempbuf3 , 0 , sizeof(Tempbuf3));

			if(GetScanf(MMI_LETTER|MMI_PWD, 4, 4, Tempbuf3, 30, LINE4 , LINE4 ,16)== ENTER ){
				changePassUser(USER_FILE_IN, Tempbuf, Tempbuf3);
		}
	}
}



int changePassUser(char *UserFileName, char *user_id ,char *user_password){

	int UserFileLen=0, ret=0, PacketTotalLen=0;
	char *pUserFile=NULL;
	char str[20];

	memmove(user_id, user_id+1, strlen(user_id));
	memmove(user_password, user_password+1, strlen(user_password));

	strcpy(str, "{ user_id=");
	strcat(str, user_id);

	if (UserFileName == NULL)
		return -1;
	UserFileLen = GetFileSize_Api(UserFileName);
	if (UserFileLen == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existen usuarios5", 3);
		return -2;
	}

	pUserFile = (char *)malloc(UserFileLen+1);

	if (pUserFile == NULL)
		return -3;
	ret = ReadFile_Api(UserFileName, pUserFile, 0, &UserFileLen);
	if (ret)
	{
		free(pUserFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error lectura usuarios", 3);
		return -4;
	}

	if( isSubstring(pUserFile, str)!=-1){

		PacketTotalLen = isSubstring(pUserFile, user_id);

		WriteFile_Api(UserFileName, (unsigned char*)user_password, PacketTotalLen+19, strlen(user_password));
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("cambio exitoso", 3);
	}
	else{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("usuario no existe", 3);
	}

}

int InputDelUser(void)
{
	char Tempbuf[10];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Id:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){
		delUser(USER_FILE_IN, Tempbuf);

	}
}

int delUser(char *UserFileName, char *user_id){

	int UserFileLen=0, ret=0, PacketTotalLen=0;
	char *pUserFile=NULL;

	memmove(user_id, user_id+1, strlen(user_id));

	if (UserFileName == NULL)
		return -1;
	UserFileLen = GetFileSize_Api(UserFileName);
	if (UserFileLen == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existen usuarios6", 3);
		return -2;
	}

	pUserFile = (char *)malloc(UserFileLen+1);

	if (pUserFile == NULL)
		return -3;
	ret = ReadFile_Api(UserFileName, pUserFile, 0, &UserFileLen);
	if (ret)
	{
		free(pUserFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error lectura usuarios", 3);
		return -4;
	}
	if( isSubstring(pUserFile, user_id)!=-1 && strcmp(user_id, "1234")!=0 && strcmp(user_id, "1267")!=0){

	PacketTotalLen = isSubstring(pUserFile, user_id);

	WriteFile_Api(UserFileName, (unsigned char*)"                                                               ", PacketTotalLen-strlen("{ user_id="),strlen("                                                               "));
	
	ScrClrLine_Api(LINE2, LINE6);
	ErrorPrompt("usuario borrado", 3);
	}
	else{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("usuario no existe", 3);
	}
}

 int isSubstring(char * haystack, char * needle) {
     int i = 0;
     int d = 0;
     if (strlen(haystack) >= strlen(needle)) {
         for (i = strlen(haystack) - strlen(needle); i >= 0; i--) {
             int found = 1;
             for (d = 0; d < strlen(needle); d++) {
                 if (haystack[i + d] != needle[d]) {
                     found = 0; 
                     break;
                 }
             }
             if (found == 1) {
                 return i;
             }
         }
         return -1;
     } else {
         //fprintf(stdout, "haystack smaller\n"); 
     }
 } 

 int KeyLoad(char *KeyFileName)	
{
	int KeyFileLen=0, ret=0, PacketTotalLen=0, OnePacketLen=0, PacketNum=0, i=0;
	char *pKeyFile=NULL, *p=NULL, *q=NULL, *pTemp=NULL, TempBuf[256], DispBuf[32], keyval[33], checkval[7];
	RUSSIA_KEYSET_STR keyset;

	ScrCls_Api();
	DispTitle("Carga de llaves");
	ScrDisp_Api(LINE3, 0, "Procesando...", FDISP|CDISP);


	KeyFileLen = GetFileSize_Api(KeyFileName);
	if (KeyFileLen == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt(KeyFileName, 3);
		return -2;
	}

	pKeyFile = (char *)malloc(KeyFileLen+1);
	if (pKeyFile == NULL)
		return -3;
	ret = ReadFile_Api(KeyFileName, pKeyFile, 0, &KeyFileLen);
	if (ret)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error de formato 1", 3);
		return -4;
	}

	p = strstr(pKeyFile, "<keyset>\r\n");
	if (p == NULL)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error de formato 2", 3);
		return -5;
	}
	q = strstr(pKeyFile, "</keyset>");
	if (q == NULL)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error de formato 3", 3);
		return -6;
	}
	PacketTotalLen = q-(p+strlen("<keyset>\r\n"));
	p = NULL;
	q = NULL;
	pTemp = p = strstr(pKeyFile, "\r\n<packet");
	if (p == NULL)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error de formato 4", 3);
		return -7;
	}	
	q = strstr(pKeyFile, "</packet>\r\n");
	if (q == NULL)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error de formato 5", 3);
		return -8;
	}
	OnePacketLen = q+strlen("</packet>\r\n")-p;

	PacketNum = (PacketTotalLen/OnePacketLen)+1;

	for (i=0; i<PacketNum; i++)
	{

		memset(DispBuf, 0, sizeof(DispBuf));
		sprintf(DispBuf, "[%d/%d]", i+1, PacketNum);
		ScrDisp_Api(LINE4, 0, DispBuf, FDISP|CDISP);
		Delay_Api(100);

		memset(&keyset, 0, sizeof(RUSSIA_KEYSET_STR));
		memset(keyval, 0, sizeof(keyval));
		memset(checkval, 0, sizeof(checkval));
		memset(TempBuf, 0, sizeof(TempBuf));

		memcpy(TempBuf, pTemp+OnePacketLen*i, OnePacketLen);

		FindPacketTagValue(TempBuf, "number", keyset.packet_number);
		FindPacketTagValue(TempBuf, "type", keyset.key_type);
		FindPacketTagValue(TempBuf, "name", keyset.key_name);
		FindPacketTagValue(TempBuf, "keyval", keyval);
		AscToBcd_Api(keyset.key_keyval, keyval, 32);
		FindPacketTagValue(TempBuf, "checkval", checkval);
		AscToBcd_Api(keyset.key_checkval, checkval, 6);

		ret = WriteFile_Api(RUSSIA_KEYFILE, (u8 *)&keyset, i*sizeof(RUSSIA_KEYSET_STR), sizeof(RUSSIA_KEYSET_STR));
		if (ret)
		{
			free(pKeyFile);
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("error guardado", 3);
			return -10;
		}

	}
	gCtrlParam.AllKeyNum = PacketNum;
	SaveCtrlParam();

	free(pKeyFile);
	KeyDeliver(KeyFileName);
	return 0;
}


int InputPackNameInfo(void)
{
	char Tempbuf[10];
	char KeyFileName[100], configFileText[100], downloads[20];
	int downloadValue=0;
	FILE *fp;

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){

		fp = fopen (CONFIG_FILE_IN, "r"); fgets (configFileText, 100, fp);

		if(fp==NULL){
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("no existe config", 3);
			return -2;
		}else{
		fclose(fp);
		}

		strcpy(downloads, strtok(configFileText , " "));

		memmove(downloads, downloads+12, strlen(downloads));
	
		downloadValue= atoi(downloads);

		if(downloadValue<20000){

		memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));

		strcpy(KeyFileName, "‪‪/mtd0/dll/");
		strcat(KeyFileName, Tempbuf);
		strcat(KeyFileName, ".xml");

		while(KeyFileName[0]!='/'){

		memmove(KeyFileName, KeyFileName+1, strlen(KeyFileName));

		}
		if(KeyFileName[0]=='/'){

		KeyLoad(KeyFileName);
		}
		}
		else{
			ScrCls_Api();
			ErrorPrompt("Reinicie inyecc", 3);
		
		}
	}
}

int InputPackName2Info(void)
{
	char Tempbuf[10];

	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	ScrCls_Api();
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE2 , 0 , "Nombre paquete:", FDISP|LDISP|INCOL);
	memset(Tempbuf , 0 , sizeof(Tempbuf));
	
	if(GetScanf(MMI_LETTER, 4, 4, Tempbuf, 30, LINE4 , LINE4 ,16)== ENTER ){
		memmove(Tempbuf, Tempbuf+1, strlen(Tempbuf));
			 KeyLoadSecond(Tempbuf);
		}
}


int KeyLoadSecond(char *packName)
{
	int KeyFileLen=0, ret=0, PacketTotalLen=0, OnePacketLen=0, PacketNum=0, i=0;
	char *pKeyFile=NULL, *p=NULL, *q=NULL, *pTemp=NULL, TempBuf[256], DispBuf[32], keyval[33], checkval[7], index[2+1];
	char KeyFileName[100];
	RUSSIA_KEYSET_SECOND_STR keyset;

	strcpy(KeyFileName, "/mtd0/dll/");
	strcat(KeyFileName, packName);
	strcat(KeyFileName, ".xml");

	ScrCls_Api();
	DispTitle("Carga de llaves");
	ScrDisp_Api(LINE3, 0, "Procesando...", FDISP|CDISP);

	if (KeyFileName == NULL)
		return -1;
	KeyFileLen = GetFileSize_Api(KeyFileName);
	if (KeyFileLen == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe archivo", 3);
		return -2;
	}

	pKeyFile = (char *)malloc(KeyFileLen+1);
	if (pKeyFile == NULL)
		return -3;
	ret = ReadFile_Api(KeyFileName, pKeyFile, 0, &KeyFileLen);
	if (ret)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error en lectura", 3);
		return -4;
	}

	p = strstr(pKeyFile, "<keyset>\r\n");
	if (p == NULL)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error de formato 7", 3);
		return -5;
	}
	q = strstr(pKeyFile, "</keyset>");
	if (q == NULL)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error de formato 8", 3);
		return -6;
	}
	PacketTotalLen = q-(p+strlen("<keyset>\r\n"));

	p = NULL;
	q = NULL;
	pTemp = p = strstr(pKeyFile, "\r\n<packet");
	if (p == NULL)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error de formato 9", 3);
		return -7;
	}	
	q = strstr(pKeyFile, "</packet>\r\n");
	if (q == NULL)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error de formato 10", 3);
		return -8;
	}
	OnePacketLen = q+strlen("</packet>\r\n")-p;

	if (PacketTotalLen%OnePacketLen != 0)
	{
		free(pKeyFile);
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("error de formato 11", 3);
		return -9;
	}
	PacketNum = PacketTotalLen/OnePacketLen;

	for (i=0; i<PacketNum; i++)
	{

		memset(DispBuf, 0, sizeof(DispBuf));
		sprintf(DispBuf, "[%d/%d]", i+1, PacketNum);
		ScrDisp_Api(LINE4, 0, DispBuf, FDISP|CDISP);
		Delay_Api(100);

		memset(&keyset, 0, sizeof(RUSSIA_KEYSET_SECOND_STR));
		memset(keyval, 0, sizeof(keyval));
		memset(checkval, 0, sizeof(checkval));
		memset(index, 0, sizeof(index));
		memset(TempBuf, 0, sizeof(TempBuf));

		memcpy(TempBuf, pTemp+OnePacketLen*i, OnePacketLen);

		FindPacketTagValue(TempBuf, "number", keyset.packet_number);
		FindPacketTagValue(TempBuf, "keytype1", keyset.key_type1);
		FindPacketTagValue(TempBuf, "name1", keyset.key_name1);
		FindPacketTagValue(TempBuf, "index1", index);
		keyset.index1 = (char)AscToLong_Api(index, (u8)strlen(index));
		FindPacketTagValue(TempBuf, "keyval1", keyval);
		AscToBcd_Api(keyset.key_keyval1, keyval, 32);
		FindPacketTagValue(TempBuf, "checkval1", checkval);
		AscToBcd_Api(keyset.key_checkval1, checkval, 6);

		FindPacketTagValue(TempBuf, "keytype2", keyset.key_type2);
		FindPacketTagValue(TempBuf, "name2", keyset.key_name2);
		memset(index, 0, sizeof(index));
		FindPacketTagValue(TempBuf, "index2", index);
		keyset.index2 = (char)AscToLong_Api(index, (u8)strlen(index));
		memset(keyval, 0, sizeof(keyval));
		FindPacketTagValue(TempBuf, "keyval2", keyval);
		AscToBcd_Api(keyset.key_keyval2, keyval, 32);
		memset(checkval, 0, sizeof(checkval));
		FindPacketTagValue(TempBuf, "checkval2", checkval);
		AscToBcd_Api(keyset.key_checkval2, checkval, 6);

		ret = WriteFile_Api(RUSSIA_KEYFILE, (u8 *)&keyset, i*sizeof(RUSSIA_KEYSET_SECOND_STR), sizeof(RUSSIA_KEYSET_SECOND_STR));
		if (ret)
		{
			free(pKeyFile);
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("error en guardado", 3);
			return -10;
		}

	}
	gCtrlParam.AllKeyNum = PacketNum;
	SaveCtrlParam();

	free(pKeyFile);
	return 0;
}




int CheckPacketNumber(unsigned char *PacketNumber, RUSSIA_KEYSET_STR *keyset, int *ReDevilerFlag)
{
	int KeyFileLen=0, ret=0, KeyNum=0, ReadPacketLen=0, i=0, FindNumber=0, Usable=0;
	RUSSIA_KEYSET_STR TempKeyset;

	//
	KeyFileLen = GetFileSize_Api(RUSSIA_KEYFILE);
	if (KeyFileLen == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe keyfile", 3);
		return -1;
	}
	KeyNum = KeyFileLen/sizeof(RUSSIA_KEYSET_STR);
	//
	for (i=0; i<KeyNum; i++)
	{
		ReadPacketLen = sizeof(RUSSIA_KEYSET_STR);
		memset(&TempKeyset, 0, sizeof(RUSSIA_KEYSET_STR));
		ret = ReadFile_Api(RUSSIA_KEYFILE, (u8 *)&TempKeyset, i*sizeof(RUSSIA_KEYSET_STR), &ReadPacketLen);
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("error en lectura", 3);
			return -2;
		}
		if (PacketNumber != NULL)
		{
			if (memcmp(PacketNumber, TempKeyset.packet_number, 10) == 0)
			{
				FindNumber = 1;
				if (TempKeyset.isUsed == 0)
					Usable = 1;	
				else
					Usable = 0;
				break;
			}
		} 
		else
		{
			if (TempKeyset.isUsed == 0)
			{
				FindNumber = 1;
				Usable = 1;
				break;
			}

		}
	}
	if ((FindNumber==1) && (Usable == 1))
	{

		memset(keyset, 0, sizeof(RUSSIA_KEYSET_STR));
		memcpy(keyset , &TempKeyset , sizeof(RUSSIA_KEYSET_STR));
		gCtrlParam.CurKeyNum = i;
		SaveCtrlParam();
		return 0;
	}
	else if ((FindNumber==1) && (Usable == 0))
	{

		Beep_Api(1);
		ScrClrLine_Api(LINE2, LINE6);
		ScrDisp_Api(LINE2 , 0 , "Ha sido usada", FDISP|CDISP|INCOL); 
//		ScrDisp_Api(LINE3 , 0 , "Whether Redeliver?", FDISP|CDISP|INCOL); 
		ScrDisp_Api(LINE3 , 0 , "Utilice siguiente llave", FDISP|CDISP|INCOL); 
		if(WaitEnterAndEscKey_Api(30) == ENTER)
		{
// 			memcpy(keyset , &TempKeyset , sizeof(RUSSIA_KEYSET_STR));
// 			gCtrlParam.CurKeyNum = i;
// 			SaveCtrlParam();
// 			*ReDevilerFlag = 1;
// 			return 0;
			return ENTER;
		}
		else
			return -3;

	}
	else
	{

		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no llaves disponibles", 3);
		return -4;
	}

}




int CheckPacketNumberSecond(unsigned char *PacketNumber, RUSSIA_KEYSET_SECOND_STR *keyset, int *ReDevilerFlag)
{
	int KeyFileLen=0, ret=0, KeyNum=0, ReadPacketLen=0, i=0, FindNumber=0, Usable=0;
	RUSSIA_KEYSET_SECOND_STR TempKeyset;
	
	
	KeyFileLen = GetFileSize_Api(RUSSIA_KEYFILE);
	if (KeyFileLen == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe keyfile", 3);
		return -1;
	}
	KeyNum = KeyFileLen/sizeof(RUSSIA_KEYSET_SECOND_STR);
	
	for (i=0; i<KeyNum; i++)
	{
		ReadPacketLen = sizeof(RUSSIA_KEYSET_SECOND_STR);
		memset(&TempKeyset, 0, sizeof(RUSSIA_KEYSET_SECOND_STR));
		ret = ReadFile_Api(RUSSIA_KEYFILE, (u8 *)&TempKeyset, i*sizeof(RUSSIA_KEYSET_SECOND_STR), &ReadPacketLen);
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("error en lectura", 3);
			return -2;
		}
		if (PacketNumber != NULL)
		{
			if (memcmp(PacketNumber, TempKeyset.packet_number, 7) == 0)
			{
				FindNumber = 1;
				if (TempKeyset.isUsed == 0)
					Usable = 1;	
				else
					Usable = 0;	
				break;
			}
		} 
		else
		{
			if (TempKeyset.isUsed == 0)
			{
				FindNumber = 1;
				Usable = 1;
				break;
			}
			
		}
	}
	if ((FindNumber==1) && (Usable == 1))
	{
	
		memset(keyset, 0, sizeof(RUSSIA_KEYSET_SECOND_STR));
		memcpy(keyset , &TempKeyset , sizeof(RUSSIA_KEYSET_SECOND_STR));
		gCtrlParam.CurKeyNum = i;
		SaveCtrlParam();
		return 0;
	}
	else if ((FindNumber==1) && (Usable == 0))
	{

		Beep_Api(1);
		ScrClrLine_Api(LINE2, LINE6);
		ScrDisp_Api(LINE2 , 0 , "Ha sido usada", FDISP|CDISP|INCOL); 
//		ScrDisp_Api(LINE3 , 0 , "Whether Redeliver?", FDISP|CDISP|INCOL); 
		ScrDisp_Api(LINE3 , 0 , "Use siguiente llave", FDISP|CDISP|INCOL); 
		if(WaitEnterAndEscKey_Api(30) == ENTER)
		{
// 			memcpy(keyset , &TempKeyset , sizeof(RUSSIA_KEYSET_STR));
// 			gCtrlParam.CurKeyNum = i;
// 			SaveCtrlParam();
// 			*ReDevilerFlag = 1;
// 			return 0;
			return ENTER;
		}
		else
			return -3;
		
	}
	else
	{

		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no llave disponible", 3);
		return -4;
	}
	
}


int GetClearMK(RUSSIA_KEYSET_STR *keyset, char *MKBuf)
{
	int i=0;
//	BOOL parity = FALSE;	// Bandera de juicio inicial, 1 en el byte es la paridad impar es verdadera, la paridad par es falsa
	char ComponentOne[17], ComponentTwo[17], CombinedKey[17], TempBuf[17], ChkValue[17], Zero[9];
	char ZeroBuf[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

	memset(ComponentOne, 0, sizeof(ComponentOne));
	memset(ComponentTwo, 0, sizeof(ComponentTwo));
	memset(CombinedKey, 0, sizeof(CombinedKey));
	memset(TempBuf, 0, sizeof(TempBuf));
	memset(ChkValue, 0, sizeof(ChkValue));
	memset(Zero, 0, sizeof(Zero));

	/*if ((memcmp(&gCtrlParam.OneKey[gCtrlParam.KEKIndex][0], ZeroBuf,16) == 0) ||
		(memcmp(&gCtrlParam.TwoKey[gCtrlParam.KEKIndex][0], ZeroBuf,16) == 0))
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no component input", 3);
		return -1;
	}*/
	
	memcpy(ComponentOne, &gCtrlParam.OneKey[gCtrlParam.KEKIndex][0], 16);	
	memcpy(ComponentTwo, &gCtrlParam.TwoKey[gCtrlParam.KEKIndex][0], 16);	

	for(i=0; i<16; i++)	
	{
		CombinedKey[i] = ComponentOne[i] ^ ComponentTwo[i];
	}

	Des3Calc_Api(keyset->key_keyval, TempBuf, keyset->key_keyval, 0);

	Des3Calc_Api(keyset->key_keyval+8, TempBuf+8, keyset->key_keyval+8, 0);

	//Des3Calc_Api(Zero, ChkValue, TempBuf, 1);
	/*if (memcmp(ChkValue, keyset->key_checkval, 3) != 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt(ChkValue, 3);

		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt(keyset->key_checkval, 3);
		return -2;	
	}*/

	
	memcpy(MKBuf, TempBuf, 16);

	return 0;
}



int GetClearMKMC(RUSSIA_KEYSET_SECOND_STR *keyset, char *MKBuf, char *MCBuf)
{
	int i=0;
	//	BOOL parity = FALSE;	// Bandera de juicio inicial, 1 en el byte es la paridad impar es verdadera, la paridad par es falsa
	char ComponentOne[17], ComponentTwo[17], CombinedKey[17], TempBuf[17], ChkValue[17], Zero[9];
	char ZeroBuf[]="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
	
	memset(ComponentOne, 0, sizeof(ComponentOne));
	memset(ComponentTwo, 0, sizeof(ComponentTwo));
	memset(CombinedKey, 0, sizeof(CombinedKey));
	memset(TempBuf, 0, sizeof(TempBuf));
	memset(ChkValue, 0, sizeof(ChkValue));
	memset(Zero, 0, sizeof(Zero));

	memcpy(&gCtrlParam.OneKey[gCtrlParam.KEKIndex][0], ZeroBuf,16);
	memcpy(&gCtrlParam.TwoKey[gCtrlParam.KEKIndex][0], ZeroBuf,16);
	
	if ((memcmp(&gCtrlParam.OneKey[gCtrlParam.KEKIndex][0], ZeroBuf,16) == 0) ||
		(memcmp(&gCtrlParam.TwoKey[gCtrlParam.KEKIndex][0], ZeroBuf,16) == 0))
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no componente", 3);
		return -1;
	}
	memcpy(ComponentOne, &gCtrlParam.OneKey[gCtrlParam.KEKIndex][0], 16);	
	memcpy(ComponentTwo, &gCtrlParam.TwoKey[gCtrlParam.KEKIndex][0], 16);	
	

	for(i=0; i<16; i++)	
	{
		CombinedKey[i] = ComponentOne[i] ^ ComponentTwo[i];
	}

	Des3Calc_Api(keyset->key_keyval1, TempBuf, CombinedKey, 0);
	Des3Calc_Api(keyset->key_keyval1+8, TempBuf+8, CombinedKey, 0);

	Des3Calc_Api(Zero, ChkValue, TempBuf, 1);
	if (memcmp(ChkValue, keyset->key_checkval1, 3) != 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("llave MK checkval error", 3);
		return -2;	
	}
	
	memcpy(MKBuf, TempBuf, 16);
	

	memset(TempBuf, 0, sizeof(TempBuf));
	Des3Calc_Api(keyset->key_keyval2, TempBuf, CombinedKey, 0);
	Des3Calc_Api(keyset->key_keyval2+8, TempBuf+8, CombinedKey, 0);

	memset(ChkValue, 0, sizeof(ChkValue));
	Des3Calc_Api(Zero, ChkValue, TempBuf, 1);
	if (memcmp(ChkValue, keyset->key_checkval2, 3) != 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("llave MK checkval error", 3);
		return -3;	
	}
	
	memcpy(MCBuf, TempBuf, 16);
	
	return 0;
}


int SendRecvToPos(RUSSIA_KEYSET_STR *keyset, char *MKBuf, char *RecvData, char *keysLong)
{
	int ret=0, loc=0, i=0, DataLen=0;
	signed int TimerId=0, RecvLen=0, ExpectLen=3, nCurrent=0;
	char SendRecvBuf[512], Dispbuf[1024];

	memset(SendRecvBuf, 0, sizeof(SendRecvBuf));
	memset(Dispbuf, 0, sizeof(Dispbuf));
	
	SendRecvBuf[loc++] = STX;
	
	loc += 2;
	
	memcpy(SendRecvBuf+loc, keyset->packet_number, 10);
	loc += 10;
	
	SendRecvBuf[loc++] = gCtrlParam.MKIndex;

	memcpy(SendRecvBuf+loc, keyset->key_type, 3);
	loc += 3;
	
	memcpy(SendRecvBuf+loc, keyset->key_checkval, 3);
	loc += 3;

	memcpy(SendRecvBuf+loc, keysLong, 11);
	loc += 11;

	if(strcmp(keysLong,"keysLong=48")==0){
		memcpy(SendRecvBuf+loc, keyset->key_keyval, 24);
		loc += 24;
	}
	if(strcmp(keysLong,"keysLong=32")==0){
		memcpy(SendRecvBuf+loc, keyset->key_keyval, 16);
		loc += 16;
	}

	//-STX(1)-Len(2)+XOR(1)
	SendRecvBuf[1] = (loc-1-2+1)/256;	
	SendRecvBuf[2] = (loc-1-2+1)%256;
	
	SendRecvBuf[loc++] = XorCalc_Api(&SendRecvBuf[1], loc-1);
	
	SendRecvBuf[loc++] = ETX;

	ret = initCom(gCtrlParam.ComNo, COM_BAUD, 8, 0, 1);
	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("Fallo al iniciar puerto", 3);
		return -1;
	}

	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE3, 0 ,"Enviando...", FDISP|CDISP|INCOL);
	Delay_Api(100);

	ret = PortSends_Api(gCtrlParam.ComNo, SendRecvBuf, loc);
	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("Send data failed", 3);
		return -2;
	}

	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE3, 0 ,"Recibiendo...", FDISP|CDISP);
	Delay_Api(100);
	memset(SendRecvBuf, 0, sizeof(SendRecvBuf));
	TimerId = TimerSet_Api();
	while(1)
	{
		if (TimerCheck_Api(TimerId, 10*1000))
			return -3;
		
		RecvLen = PortRecv_Api(gCtrlParam.ComNo, SendRecvBuf+nCurrent, ExpectLen, 500);
		if (RecvLen <= 0 )
			continue;

		if(nCurrent == 0)
		{
			for (i=0; i<RecvLen; i++)
			{
				if (SendRecvBuf[i] == 0x02)
					break;
			}
			if(i == RecvLen)
				continue;
			nCurrent = RecvLen - i;
			memmove(SendRecvBuf, SendRecvBuf+i, nCurrent);
		}
		else 
			nCurrent += RecvLen;


		if (nCurrent >= 3)//0x02+Len(2)
		{
			DataLen = SendRecvBuf[1]*256+SendRecvBuf[2];
			if (nCurrent >= DataLen+4)//0x02+Len(2)+0x03
			{
				nCurrent = DataLen+4;
				break;
			}
			ExpectLen = DataLen+1;
		}
		else
			ExpectLen = 3-nCurrent;
	}

	if (SendRecvBuf[nCurrent-2] != XorCalc_Api(SendRecvBuf+1, DataLen+2-1))//+Len(2)-XOR(1)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("Data Check Error", 3);
		return -4;
	}

	memcpy(RecvData, SendRecvBuf, nCurrent);
	return 0;
}



int SendRecvToPosSecond(RUSSIA_KEYSET_SECOND_STR *keyset, char *MKBuf, char *MCBuf, char *RecvData)
{
	int ret=0, loc=0, i=0, DataLen=0;
	signed int TimerId=0, RecvLen=0, ExpectLen=3, nCurrent=0;
	char SendRecvBuf[512];

	memset(SendRecvBuf, 0, sizeof(SendRecvBuf));
	
	
	SendRecvBuf[loc++] = STX;
	
	loc += 2;
	
	memcpy(SendRecvBuf+loc, keyset->packet_number, 7);
	loc += 7;
	
	SendRecvBuf[loc++] = keyset->index1;//keyset->index1
	
	memcpy(SendRecvBuf+loc, MKBuf, 16);
	loc += 16;
	
	memcpy(SendRecvBuf+loc, keyset->key_checkval1, 3);
	loc += 3;
	
	SendRecvBuf[loc++] = keyset->index2;//keyset->index2
	
	memcpy(SendRecvBuf+loc, MCBuf, 16);
	loc += 16;
	
	memcpy(SendRecvBuf+loc, keyset->key_checkval2, 3);
	loc += 3;
	//-STX(1)-Len(2)+XOR(1)
	SendRecvBuf[1] = (loc-1-2+1)/256;	
	SendRecvBuf[2] = (loc-1-2+1)%256;
	
	SendRecvBuf[loc++] = XorCalc_Api(&SendRecvBuf[1], loc-1);
	
	SendRecvBuf[loc++] = ETX;
	
	ret = initCom(gCtrlParam.ComNo, COM_BAUD, 8, 0, 1);
	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("open ComPort failed", 3);
		return -1;
	}
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE3, 0 ,"Sending...", FDISP|CDISP|INCOL);//·¢ËÍÖÐ
	Delay_Api(100);
	ret = PortSends_Api(gCtrlParam.ComNo, SendRecvBuf, loc);
	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("Send  data failed", 3);
		return -2;
	}

	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE3, 0 ,"Recving...", FDISP|CDISP);//·¢ËÍÖÐ
	Delay_Api(100);
	memset(SendRecvBuf, 0, sizeof(SendRecvBuf));
	TimerId = TimerSet_Api();
	while(1)
	{
		if (TimerCheck_Api(TimerId, 10*1000))
			return -3;
		
		RecvLen = PortRecv_Api(gCtrlParam.ComNo, SendRecvBuf+nCurrent, ExpectLen, 500);
		if (RecvLen <= 0 )
			continue;

		if(nCurrent == 0)
		{
			for (i=0; i<RecvLen; i++)
			{
				if (SendRecvBuf[i] == 0x02)
					break;
			}
			if(i == RecvLen)
				continue;
			nCurrent = RecvLen - i;
			memmove(SendRecvBuf, SendRecvBuf+i, nCurrent);
		}
		else 
			nCurrent += RecvLen;

		if (nCurrent >= 3)//0x02+Len(2)
		{
			DataLen = SendRecvBuf[1]*256+SendRecvBuf[2];
			if (nCurrent >= DataLen+4)//0x02+Len(2)+0x03
			{
				nCurrent = DataLen+4;
				break;
			}
			ExpectLen = DataLen+1;
		}
		else
			ExpectLen = 3-nCurrent;
	}

	if (SendRecvBuf[nCurrent-2] != XorCalc_Api(SendRecvBuf+1, DataLen+2-1))//+Len(2)-XOR(1)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("Data Check Error", 3);
		return -4;
	}

	memcpy(RecvData, SendRecvBuf, nCurrent);
	return 0;
}


int SaveKeylog(RUSSIA_KEYSET_STR *keyset, char *RecvData)
{
	int ret=0, FileLen=0, Num=0, i=0, StuSize=0;
	char TimeBuf[16];
	RUSSIA_KEYLOG_STR keylog, Tempkeylog;

	memset(TimeBuf, 0, sizeof(TimeBuf));
	memset(&keylog, 0, sizeof(RUSSIA_KEYLOG_STR));
	memset(&Tempkeylog, 0, sizeof(RUSSIA_KEYLOG_STR));
	
	memcpy(keylog.type, keyset->key_type, 2);
	memcpy(keylog.name, keyset->key_name, 3);
	memcpy(keylog.checkval, keyset->key_checkval, 3);
	memcpy(keylog.id, RecvData+1+2, 7);	//+1STX+2LEN
	memcpy(keylog.serialnumber, RecvData+1+2+7, 11);	//+1STX+2LEN+7SEQ
	memcpy(keylog.timestamp, RecvData+1+2+7+11, 14);	//+1STX+2LEN+7SEQ+11SN
	
	FileLen = GetFileSize_Api(RUSSIA_KEYLOG);
	if (FileLen == 0)
	{
		ret = WriteFile_Api(RUSSIA_KEYLOG, (u8 *)&keylog, 0, sizeof(RUSSIA_KEYLOG_STR));
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE5);
			ErrorPrompt("Save file failed", 3);
			return -1;
		}
		return 0;

	}
	Num = FileLen/sizeof(RUSSIA_KEYLOG_STR);
	for (i=0; i<Num; i++)
	{
		StuSize = sizeof(RUSSIA_KEYLOG_STR);
		ret = ReadFile_Api(RUSSIA_KEYLOG, (u8 *)&Tempkeylog, i*StuSize, &StuSize);
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE5);
			ErrorPrompt("read file failed", 3);
			return -2;
		}
		if (memcmp(Tempkeylog.id, keylog.id, 7)==0)
		{
			ret = WriteFile_Api(RUSSIA_KEYLOG, (u8 *)&keylog, i*sizeof(RUSSIA_KEYLOG_STR), sizeof(RUSSIA_KEYLOG_STR));
			if (ret)
			{
				ScrClrLine_Api(LINE2, LINE5);
				ErrorPrompt("Save file failed", 3);
				return -3;
			}
			return 0;
		}
	}
	ret = WriteFile_Api(RUSSIA_KEYLOG, (u8 *)&keylog, FileLen, sizeof(RUSSIA_KEYLOG_STR));
	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE5);
		ErrorPrompt("Save file failed", 3);
		return -4;
	}
	return 0;
}




int SaveKeylogSecond(RUSSIA_KEYSET_SECOND_STR *keyset, char *RecvData)
{
	int ret=0, FileLen=0, Num=0, i=0, StuSize=0;
	char TimeBuf[16];
	RUSSIA_KEYLOG_SECOND_STR keylog, Tempkeylog;
	
	memset(TimeBuf, 0, sizeof(TimeBuf));
	memset(&keylog, 0, sizeof(RUSSIA_KEYLOG_SECOND_STR));
	memset(&Tempkeylog, 0, sizeof(RUSSIA_KEYLOG_SECOND_STR));
	
	memcpy(keylog.type1, keyset->key_type1, 2);
	memcpy(keylog.name1, keyset->key_name1, 3);
	memcpy(keylog.checkval1, keyset->key_checkval1, 3);
	memcpy(keylog.type2, keyset->key_type2, 2);
	memcpy(keylog.name2, keyset->key_name2, 3);
	memcpy(keylog.checkval2, keyset->key_checkval2, 3);
	memcpy(keylog.id, RecvData+1+2, 7);	//+1STX+2LEN
	memcpy(keylog.serialnumber, RecvData+1+2+7, 11);	//+1STX+2LEN+7SEQ
	memcpy(keylog.timestamp, RecvData+1+2+7+11, 14);	//+1STX+2LEN+7SEQ+11SN
	
	FileLen = GetFileSize_Api(RUSSIA_KEYLOG);
	if (FileLen == 0)
	{
		ret = WriteFile_Api(RUSSIA_KEYLOG, (u8 *)&keylog, 0, sizeof(RUSSIA_KEYLOG_SECOND_STR));
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE5);
			ErrorPrompt("Save file failed", 3);
			return -1;
		}
		return 0;
		
	}
	Num = FileLen/sizeof(RUSSIA_KEYLOG_SECOND_STR);
	for (i=0; i<Num; i++)
	{
		StuSize = sizeof(RUSSIA_KEYLOG_SECOND_STR);
		ret = ReadFile_Api(RUSSIA_KEYLOG, (u8 *)&Tempkeylog, i*StuSize, &StuSize);
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE5);
			ErrorPrompt("read file failed", 3);
			return -2;
		}
		if (memcmp(Tempkeylog.id, keylog.id, 7)==0)
		{
			ret = WriteFile_Api(RUSSIA_KEYLOG, (u8 *)&keylog, i*sizeof(RUSSIA_KEYLOG_SECOND_STR), sizeof(RUSSIA_KEYLOG_SECOND_STR));
			if (ret)
			{
				ScrClrLine_Api(LINE2, LINE5);
				ErrorPrompt("Save file failed", 3);
				return -3;
			}
			return 0;
		}
	}
	ret = WriteFile_Api(RUSSIA_KEYLOG, (u8 *)&keylog, FileLen, sizeof(RUSSIA_KEYLOG_SECOND_STR));
	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE5);
		ErrorPrompt("Save file failed", 3);
		return -4;
	}
	return 0;
}


int KeyDeliver(char *KeyFileName)
{
	int ret=0, ReDevilerFlag=0, downloadValue=0, k=0, downloadValue2=0, u=0;
	char packName[20], packNumber[20], amountComp[20], trash[20],keysLong[20], DispBuf[32], PacketNumber[11], MKBuf[48], RecvData[512], configFileText[200],packFileText[200], downloads[20], str4[10], str5[20], downloads2[20], str6[10], str7[200];
	RUSSIA_KEYSET_STR gotKeyset;
	FILE *fp;

	memset(DispBuf, 0, sizeof(DispBuf));
	memset(PacketNumber, 0, sizeof(PacketNumber));
	memset(MKBuf, 0, sizeof(MKBuf));
	memset(RecvData, 0, sizeof(RecvData));
	memset(&gotKeyset, 0, sizeof(RUSSIA_KEYSET_STR));

	fp = fopen (KeyFileName, "r"); fgets (packFileText, 100, fp); fclose(fp);

	strcpy(trash, strtok(packFileText , " "));
	strcpy(downloads, strtok(NULL , " "));
    strcpy(packName, strtok(NULL , " "));
	strcpy(packNumber, strtok(NULL, " "));
	strcpy(amountComp , strtok(NULL, " "));
	strcpy(keysLong, strtok(NULL, " "));

	keysLong[11]=0;

	ScrCls_Api();
	DispTitle("Inyeccion");

	if(gCtrlParam.AllKeyNum == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("No existe llave", 3);
		return -1;
	}

	ScrClrLine_Api(LINE2, LINE6);
	sprintf(DispBuf , "Llave.disp[%d]" , gCtrlParam.AllKeyNum);
	ScrDisp_Api(LINE3, 0 ,DispBuf, FDISP|CDISP|INCOL);
	ScrDisp_Api(LINE5, 0 ,"[Enter]->Descargar", FDISP|CDISP|INCOL);
	ret=WaitEnterAndEscKey_Api(30);
	if( ret != ENTER )
		return -2;

AGAIN:
	ReDevilerFlag=0;
	memset(PacketNumber, 0, sizeof(PacketNumber));
	memset(MKBuf, 0, sizeof(MKBuf));
	memset(RecvData, 0, sizeof(RecvData));
	memset(&gotKeyset, 0, sizeof(RUSSIA_KEYSET_STR));
	//PacketNumber Works
	ret = InputPacketNumber(PacketNumber);
	if (ret==OK)
	{
		//PacketNumber Works
		if(strlen(PacketNumber)==4){
		strcat(PacketNumber, "000000");
		}
		ret = CheckPacketNumber(PacketNumber, &gotKeyset, &ReDevilerFlag);
		if (ret < 0)
			return -3;
		else if (ret == ENTER)
			goto AGAIN;
	}
	else
	{
		//PacketNumber no funciona, descarga la primera clave disponible
		ret = CheckPacketNumber(NULL, &gotKeyset, &ReDevilerFlag);
		if (ret < 0)
			return -4;
		else if (ret == ENTER)
			goto AGAIN;
	}

	// Confirmación de información
	ScrCls_Api();
	DispTitle("Inyeccion");
	ScrDisp_Api(LINE2, 0 ,"Confirmar info", FDISP|CDISP|INCOL);
	memset(DispBuf, 0, sizeof(DispBuf));
	sprintf(DispBuf, "KIN/KSI:%s", gotKeyset.packet_number);
	ScrDisp_Api(LINE3, 0 ,DispBuf, FDISP|LDISP|INCOL);
	memset(DispBuf, 0, sizeof(DispBuf));
	sprintf(DispBuf, "Type:%s", gotKeyset.key_type);
	ScrDisp_Api(LINE4, 0 ,DispBuf, FDISP|LDISP|INCOL);
	memset(DispBuf, 0, sizeof(DispBuf));
	strcpy(DispBuf, "Checkval:");
	BcdToAsc_Api(DispBuf+strlen(DispBuf), gotKeyset.key_checkval, 6);
	ScrDisp_Api(LINE5, 0 ,DispBuf, FDISP|LDISP|INCOL);

	if(WaitEnterAndEscKey_Api(30) != ENTER) 
		return -5;
	//Obtener texto MK
	ret = GetClearMK(&gotKeyset, MKBuf);
	if (ret)
		return -6;
	//Enviar recepción
	ret = SendRecvToPos(&gotKeyset, MKBuf, RecvData, keysLong);

	if (ret)
		return -7;

	//Post-procesamiento
	gotKeyset.isUsed = 1;
	ret = WriteFile_Api(RUSSIA_KEYFILE, (u8 *)&gotKeyset, gCtrlParam.CurKeyNum*sizeof(RUSSIA_KEYSET_STR), sizeof(RUSSIA_KEYSET_STR));

	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("Save ketset error", 3);
		return -8;
	}
	ret = SaveKeylog(&gotKeyset, RecvData);

	if (ret)
		return -9;

	if (ReDevilerFlag==0)
	{
		gCtrlParam.AllKeyNum--;
		SaveCtrlParam();
	}


	fp = fopen (CONFIG_FILE_IN, "r");

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe config", 3);
		return -2;
	}else{

		fgets (configFileText, 100, fp);

		strcpy(downloads, strtok(configFileText , " "));

		memmove(downloads, downloads+12, strlen(downloads));
	
		downloadValue= atoi(downloads);

		k=downloadValue+1;

		sprintf(str4, "%d", k);

		strcpy(str5, "inyecciones=");
		strcat(str5, str4);

		WriteFile_Api(CONFIG_FILE_IN, (unsigned char *)str5, 0, strlen(str5));

		fclose(fp);
	}

	fp = fopen (KeyFileName, "r");

	if(fp==NULL){
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no existe paq", 3);
		return -2;

	}else{
	fgets (packFileText, 100, fp);

	strcpy(trash, strtok(packFileText , " "));
	strcpy(downloads2, strtok(NULL , " "));
	strcpy(packName, strtok(NULL , " "));
	strcpy(packNumber, strtok(NULL, " "));
	strcpy(amountComp , strtok(NULL, " "));
	strcpy(keysLong, strtok(NULL, " "));

	memmove(downloads2, downloads2+10, strlen(downloads2));
	
	downloadValue2= atoi(downloads2);

	u=downloadValue2+1;

	sprintf(str6, "%d", u);

	strcpy(str7, "//");
	strcat(str7, " downloads=");
	strcat(str7, str6);
	strcat(str7, " ");
	strcat(str7, packName);
	strcat(str7, " ");
	strcat(str7, packNumber);
	strcat(str7, " ");
	strcat(str7, amountComp);
	strcat(str7, " ");
	keysLong[11]=0;
	strcat(str7, keysLong);

	WriteFile_Api(KeyFileName, (unsigned char *)str7, 0, strlen(str7));

	fclose(fp);
	}

	ScrClrLine_Api(LINE2, LINE6);

	ScrDisp_Api(LINE3, 0, "Deliver success", CDISP);
	ScrDisp_Api(LINE6, 0, "ENTER-goon ESC-exit", CDISP);

	ret = WaitEnterAndEscKey_Api(60);
	if (ret == ENTER)
		goto AGAIN;
	else
		return 10;
}


//distribución de claves
int KeyDeliverSecond(void)
{
	int ret=0, ReDevilerFlag=0;
	char DispBuf[32], PacketNumber[8], MKBuf[48], MCBuf[48], RecvData[512];
	RUSSIA_KEYSET_SECOND_STR gotKeyset;

	memset(DispBuf, 0, sizeof(DispBuf));
	memset(PacketNumber, 0, sizeof(PacketNumber));
	memset(MKBuf, 0, sizeof(MKBuf));
	memset(MCBuf, 0, sizeof(MCBuf));
	memset(RecvData, 0, sizeof(RecvData));
	memset(&gotKeyset, 0, sizeof(RUSSIA_KEYSET_SECOND_STR));

	ScrCls_Api();
	DispTitle("Key Deliver");
	//Sentencia previa
	if(gCtrlParam.AllKeyNum == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("No downloadable key", 3);// Sin clave descargable
		return -1;
	}
	// Información
	ScrClrLine_Api(LINE2, LINE6);
	sprintf(DispBuf , "AvailableKey[%d]" , gCtrlParam.AllKeyNum);// Claves descargables [%d] //También clave descargable [%d]
	ScrDisp_Api(LINE3, 0 ,DispBuf, FDISP|CDISP|INCOL);
	ScrDisp_Api(LINE5, 0 ,"[Enter]->Download", FDISP|CDISP|INCOL);// Descargar por confirmación
	ret=WaitEnterAndEscKey_Api(30);
	if( ret != ENTER )
		return -2;
	
	ScrClrLine_Api(LINE2, LINE6);
	if( CheckKeyParamPass( (u8*)"Input deliver pwd" , (u8*)"Pls input pwd:" , (u8*)gCtrlParam.KeySendOprPwd) != OK )// Por favor introduzca una contraseña de distribuidor de claves // Por favor introduzca una contraseña //0000000
		return -4;

AGAIN:
	ReDevilerFlag=0;
	memset(PacketNumber, 0, sizeof(PacketNumber));
	memset(MKBuf, 0, sizeof(MKBuf));
	memset(MCBuf, 0, sizeof(MCBuf));
	memset(RecvData, 0, sizeof(RecvData));
	memset(&gotKeyset, 0, sizeof(RUSSIA_KEYSET_SECOND_STR));
	ret = InputPacketNumber(PacketNumber);
	if (ret==OK)
	{
		//PacketNumber Works
		ret = CheckPacketNumberSecond(PacketNumber, &gotKeyset, &ReDevilerFlag);
		if (ret < 0)
			return -5;
		else if (ret == ENTER)
			goto AGAIN;
	}
	else
	{
		//PacketNumber no funciona, descarga la primera clave disponible
		ret = CheckPacketNumberSecond(NULL, &gotKeyset, &ReDevilerFlag);
		if (ret < 0)
			return -6;
		else if (ret == ENTER)
			goto AGAIN;
	}

	// Confirmación de información
	ScrCls_Api();
	DispTitle("Key Deliver");
	ScrDisp_Api(LINE2, 0 ,"Confirm information", FDISP|CDISP|INCOL);
	memset(DispBuf, 0, sizeof(DispBuf));
	sprintf(DispBuf, "Number:%s", gotKeyset.packet_number);
	ScrDisp_Api(LINE3, 0 ,DispBuf, FDISP|LDISP|INCOL);
	memset(DispBuf, 0, sizeof(DispBuf));
	sprintf(DispBuf, "MK/MC index:%d/%d", gotKeyset.index1, gotKeyset.index2);
	ScrDisp_Api(LINE4, 0 ,DispBuf, FDISP|LDISP|INCOL);
	memset(DispBuf, 0, sizeof(DispBuf));
	strcpy(DispBuf, "Chkval:");
	BcdToAsc_Api(DispBuf+strlen(DispBuf), gotKeyset.key_checkval1, 6);
	strcat(DispBuf, "/");
	BcdToAsc_Api(DispBuf+strlen(DispBuf), gotKeyset.key_checkval2, 6);
	ScrDisp_Api(LINE5, 0 ,DispBuf, FDISP|LDISP|INCOL);
	if(WaitEnterAndEscKey_Api(30) != ENTER) 
		return -7;

	ret = GetClearMKMC(&gotKeyset, MKBuf, MCBuf);
	if (ret)
		return -8;

	ret = SendRecvToPosSecond(&gotKeyset, MKBuf, MCBuf, RecvData);

	if (ret)
		return -9;

	gotKeyset.isUsed = 1;
	ret = WriteFile_Api(RUSSIA_KEYFILE, (u8 *)&gotKeyset, gCtrlParam.CurKeyNum*sizeof(RUSSIA_KEYSET_SECOND_STR), sizeof(RUSSIA_KEYSET_SECOND_STR));

	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("Save ketset error", 3);
		return -10;
	}
	ret = SaveKeylogSecond(&gotKeyset, RecvData);

	if (ret)
		return -11;

	if (ReDevilerFlag==0)
	{
		gCtrlParam.AllKeyNum--;
		SaveCtrlParam();
	}
	ScrClrLine_Api(LINE2, LINE6);

	ScrDisp_Api(LINE3, 0, "Deliver success", CDISP);
	ScrDisp_Api(LINE6, 0, "ENTER-goon ESC-exit", CDISP);
	ret = WaitEnterAndEscKey_Api(60);
	if (ret == ENTER)
		goto AGAIN;
	else
		return 0;
}

//consulta de clave
void RussiaKeyQue(void)
{
	int FileLen=0, KeyNum=0, ret=0, i=0, ReadLen=0;
	char PacketNumber[8], TempBuf[32];
	RUSSIA_KEYSET_STR keyset;

	memset(PacketNumber, 0, sizeof(PacketNumber));
	memset(&keyset, 0, sizeof(RUSSIA_KEYSET_STR));
	memset(TempBuf, 0, sizeof(TempBuf));

	ScrCls_Api();
	DispTitle("Key Que");

	FileLen = GetFileSize_Api(RUSSIA_KEYFILE);
	if (FileLen == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("No Keys", 3);// Sin clave
		return;
	}

AGAIN:
	memset(PacketNumber, 0, sizeof(PacketNumber));
	ret = InputPacketNumber(PacketNumber);
	if (ret)
		return;
	KeyNum = FileLen/sizeof(RUSSIA_KEYSET_STR);
	for (i=0; i<KeyNum; i++)
	{
		memset(&keyset, 0, sizeof(RUSSIA_KEYSET_STR));
		ReadLen = sizeof(RUSSIA_KEYSET_STR);
		ret = ReadFile_Api(RUSSIA_KEYFILE, (u8 *)&keyset, i*sizeof(RUSSIA_KEYSET_STR), &ReadLen);
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("read file failed", 3);
			return;
		}
		if (memcmp(keyset.packet_number, PacketNumber, 7) == 0)
		{
			ScrClrLine_Api(LINE2, LINE6);
			sprintf(TempBuf, "Total:%d", KeyNum);
			DispTitle(TempBuf);
			
			memset(TempBuf, 0, sizeof(TempBuf));
			strcpy(TempBuf, "Number:");
			memcpy(TempBuf+strlen(TempBuf), keyset.packet_number, 7);
			ScrDisp_Api(LINE2, 0 ,TempBuf, FDISP|LDISP|INCOL);
			
			memset(TempBuf, 0, sizeof(TempBuf));
			strcpy(TempBuf,"Type:");
			memcpy(TempBuf+strlen(TempBuf), keyset.key_type, 2);
			ScrDisp_Api(LINE3, 0 ,TempBuf, FDISP|LDISP|INCOL);
			
			memset(TempBuf, 0, sizeof(TempBuf));
			strcpy(TempBuf,"Name:");
			memcpy(TempBuf+strlen(TempBuf), keyset.key_name, 3);
			ScrDisp_Api(LINE4, 0 ,TempBuf, FDISP|LDISP|INCOL);
			
			memset(TempBuf, 0, sizeof(TempBuf));
			strcpy(TempBuf,"Checkval:");
			BcdToAsc_Api(TempBuf+strlen(TempBuf), (unsigned char*)keyset.key_checkval, 6);
			ScrDisp_Api(LINE5, 0 ,TempBuf, FDISP|LDISP|INCOL);

			if (keyset.isUsed == 1)
			{
				ScrDisp_Api(LINE6, 0 ,"[Already used]", FDISP|CDISP|INCOL);
			}
			else
			{
				ScrDisp_Api(LINE6, 0 ,"[Available]", FDISP|CDISP|INCOL);
			}
			ret = WaitEnterAndEscKey_Api(60);
			if (ret == ENTER)
				goto AGAIN;
			else
				return;

		}
	}
	if (i == KeyNum)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("No this Key", 3);
		return;
		}

}



//consulta de clave
void RussiaKeyQueSecond(void)
{
	int FileLen=0, KeyNum=0, ret=0, i=0, ReadLen=0;
	char PacketNumber[8], TempBuf[32];
	RUSSIA_KEYSET_SECOND_STR keyset;
	
	memset(PacketNumber, 0, sizeof(PacketNumber));
	memset(&keyset, 0, sizeof(RUSSIA_KEYSET_SECOND_STR));
	memset(TempBuf, 0, sizeof(TempBuf));
	
	ScrCls_Api();
	DispTitle("Key Que");
	
	FileLen = GetFileSize_Api(RUSSIA_KEYFILE);
	if (FileLen == 0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("No Keys", 3);//no existe clave
		return;
	}
	
AGAIN:
	memset(PacketNumber, 0, sizeof(PacketNumber));
	ret = InputPacketNumber(PacketNumber);
	if (ret)
		return;
	KeyNum = FileLen/sizeof(RUSSIA_KEYSET_SECOND_STR);
	for (i=0; i<KeyNum; i++)
	{
		memset(&keyset, 0, sizeof(RUSSIA_KEYSET_SECOND_STR));
		ReadLen = sizeof(RUSSIA_KEYSET_SECOND_STR);
		ret = ReadFile_Api(RUSSIA_KEYFILE, (u8 *)&keyset, i*sizeof(RUSSIA_KEYSET_SECOND_STR), &ReadLen);
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("read file failed", 3);
			return;
		}
		if (memcmp(keyset.packet_number, PacketNumber, 7) == 0)
		{
			ScrClrLine_Api(LINE2, LINE6);
			sprintf(TempBuf, "Total:%d", KeyNum);
			DispTitle(TempBuf);
			
			memset(TempBuf, 0, sizeof(TempBuf));
			strcpy(TempBuf, "Number:");
			memcpy(TempBuf+strlen(TempBuf), keyset.packet_number, 7);
			ScrDisp_Api(LINE2, 0 ,TempBuf, FDISP|LDISP|INCOL);
			
			memset(TempBuf, 0, sizeof(TempBuf));
			strcpy(TempBuf,"Type:");
			memcpy(TempBuf+strlen(TempBuf), keyset.key_type1, 2);
			strcat(TempBuf+strlen(TempBuf), "/");
			memcpy(TempBuf+strlen(TempBuf), keyset.key_type2, 2);
			ScrDisp_Api(LINE3, 0 ,TempBuf, FDISP|LDISP|INCOL);
			
			memset(TempBuf, 0, sizeof(TempBuf));
			strcpy(TempBuf,"Name:");
			memcpy(TempBuf+strlen(TempBuf), keyset.key_name1, 3);
			strcat(TempBuf+strlen(TempBuf), "/");
			memcpy(TempBuf+strlen(TempBuf), keyset.key_name2, 3);
			ScrDisp_Api(LINE4, 0 ,TempBuf, FDISP|LDISP|INCOL);
			
			memset(TempBuf, 0, sizeof(TempBuf));
			strcpy(TempBuf,"Chkval:");
			BcdToAsc_Api(TempBuf+strlen(TempBuf), keyset.key_checkval1, 6);
			strcat(TempBuf+strlen(TempBuf), "/");
			BcdToAsc_Api(TempBuf+strlen(TempBuf), keyset.key_checkval2, 6);
			ScrDisp_Api(LINE5, 0 ,TempBuf, FDISP|LDISP|INCOL);
			
			if (keyset.isUsed == 1)
			{
				ScrDisp_Api(LINE6, 0 ,"[Already used]", FDISP|CDISP|INCOL);
			}
			else
			{
				ScrDisp_Api(LINE6, 0 ,"[Available]", FDISP|CDISP|INCOL);
			}
			ret = WaitEnterAndEscKey_Api(60);
			if (ret == ENTER)
				goto AGAIN;
			else
				return;
			
		}
	}
	if (i == KeyNum)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("No this Key", 3);
		return;
	}
	
}


//exportación de archivos de clave
void ExportKeylog(void)
{
	int ret=0, KeylogFileLen=0, KeylogNum=0, i=0, ReadLen=0;
	RUSSIA_KEYLOG_STR Keylog;
	char *head = "<?xml version=\"1.0\"  encoding=\"utf-8\"?>\r\n<keylog>\r\n";
	char *end = "</keylog>";
	char record[1024], TempBuf[64], checkval[12];

// Información
	ScrCls_Api();
	DispTitle("Export Key log");
	ScrDisp_Api(LINE2, 0 ,"Pls connect", FDISP|CDISP|INCOL);
	ScrDisp_Api(LINE3, 0 ,"OTG and U-Disk", FDISP|CDISP|INCOL);
	ScrDisp_Api(LINE5, 0 ,"[Enter]->begin", FDISP|CDISP|INCOL);//°´È·ÈÏÏÂÔØ
	ret=WaitEnterAndEscKey_Api(30);
	if( ret != ENTER )
		return;
	
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE3, 0, "Processing...", CDISP);
	KeylogFileLen = GetFileSize_Api(RUSSIA_KEYLOG);
	if (KeylogFileLen==0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no keylog available", 3);
		return;
	}
	KeylogNum = KeylogFileLen/sizeof(RUSSIA_KEYLOG_STR);

	DelFile_Api(RUSSIA_KEYFILE_OUT);
	ret = WriteFile_Api(RUSSIA_KEYFILE_OUT, head, 0, strlen(head));
	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("write keylog failed", 3);
		return;
	}

	for(i=0; i<KeylogNum; i++)
	{
		ReadLen = sizeof(RUSSIA_KEYLOG_STR);
		memset(&Keylog, 0, sizeof(RUSSIA_KEYLOG_STR));
		ret = ReadFile_Api(RUSSIA_KEYLOG, (u8 *)&Keylog, i*sizeof(RUSSIA_KEYLOG_STR), &ReadLen);
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("read keylog failed", 3);
			return;
		}

		memset(record, 0, sizeof(record));
		strcpy(record, "<record  ");

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "type=\"%s\" ", Keylog.type);
		strcat(record, TempBuf);

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "name=\"%s\" ", Keylog.name);
		strcat(record, TempBuf);

		memset(TempBuf, 0, sizeof(TempBuf));
		memset(checkval, 0, sizeof(checkval));
		BcdToAsc_Api(checkval, Keylog.checkval, 6);
		sprintf(TempBuf, "checkval=\"%s\" ", checkval);
		strcat(record, TempBuf);

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "comment=\"keyid %s\" ", Keylog.id);
		strcat(record, TempBuf);

		strcat(record, "slot=\"0\" ");

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "id=\"%s\" ", Keylog.id);
		strcat(record, TempBuf);

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "timestamp=\"%s\" ", Keylog.timestamp);
		strcat(record, TempBuf);

		strcat(record, "device=\"Terminal\" ");

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "serialnumber=\"%s\" ", Keylog.serialnumber);
		strcat(record, TempBuf);

		strcat(record, "vendorid=\"UnionPay\"/>\r\n");

		//ÏÔÊ¾
		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "[%d/%d]", i+1, KeylogNum);
		ScrDisp_Api(LINE4, 0, TempBuf, FDISP|CDISP);
		Delay_Api(100);

		ret = WriteFile_Api(RUSSIA_KEYFILE_OUT, record, GetFileSize_Api(RUSSIA_KEYFILE_OUT), strlen(record));
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("write keylog failed", 3);
			return;
		}
	}
	ret = WriteFile_Api(RUSSIA_KEYFILE_OUT, end, GetFileSize_Api(RUSSIA_KEYFILE_OUT), strlen(end));
	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("write keylog failed", 3);
		return;
	}
	
	ScrClrLine_Api(LINE2, LINE6);
	ErrorPrompt("Export success", 3);
}



//exportación de archivos de clave
void ExportKeylogSecond(void)
{
	int ret=0, KeylogFileLen=0, KeylogNum=0, i=0, ReadLen=0;
	RUSSIA_KEYLOG_SECOND_STR Keylog;
	char *head = "<?xml version=\"1.0\"  encoding=\"utf-8\"?>\r\n<keylog>\r\n";
	char *end = "</keylog>";
	char record[1024], TempBuf[64], checkval[12];

	// Información
	ScrCls_Api();
	DispTitle("Export Key log");
	ScrDisp_Api(LINE2, 0 ,"Pls connect", FDISP|CDISP|INCOL);
	ScrDisp_Api(LINE3, 0 ,"OTG and U-Disk", FDISP|CDISP|INCOL);
	ScrDisp_Api(LINE5, 0 ,"[Enter]->begin", FDISP|CDISP|INCOL);//°´È·ÈÏÏÂÔØ
	ret=WaitEnterAndEscKey_Api(30);
	if( ret != ENTER )
		return;
	
	ScrClrLine_Api(LINE2, LINE6);
	ScrDisp_Api(LINE3, 0, "Processing...", CDISP);
	KeylogFileLen = GetFileSize_Api(RUSSIA_KEYLOG);
	if (KeylogFileLen==0)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("no keylog available", 3);
		return;
	}
	KeylogNum = KeylogFileLen/sizeof(RUSSIA_KEYLOG_SECOND_STR);

	DelFile_Api(RUSSIA_KEYFILE_OUT);
	ret = WriteFile_Api(RUSSIA_KEYFILE_OUT, head, 0, strlen(head));
	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("write keylog failed", 3);
		return;
	}

	for(i=0; i<KeylogNum; i++)
	{
		ReadLen = sizeof(RUSSIA_KEYLOG_SECOND_STR);
		memset(&Keylog, 0, sizeof(RUSSIA_KEYLOG_SECOND_STR));
		ret = ReadFile_Api(RUSSIA_KEYLOG, (u8 *)&Keylog, i*sizeof(RUSSIA_KEYLOG_SECOND_STR), &ReadLen);
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("read keylog failed", 3);
			return;
		}

		memset(record, 0, sizeof(record));
		strcpy(record, "<record  ");

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "type1=\"%s\" ", Keylog.type1);
		strcat(record, TempBuf);

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "name1=\"%s\" ", Keylog.name1);
		strcat(record, TempBuf);

		memset(TempBuf, 0, sizeof(TempBuf));
		memset(checkval, 0, sizeof(checkval));
		BcdToAsc_Api(checkval, (unsigned char *)Keylog.checkval1, 6);
		sprintf(TempBuf, "checkval1=\"%s\" ", checkval);
		strcat(record, TempBuf);

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "type2=\"%s\" ", Keylog.type2);
		strcat(record, TempBuf);
		
		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "name2=\"%s\" ", Keylog.name2);
		strcat(record, TempBuf);
		
		memset(TempBuf, 0, sizeof(TempBuf));
		memset(checkval, 0, sizeof(checkval));
		BcdToAsc_Api(checkval, (unsigned char *)Keylog.checkval2, 6);
		sprintf(TempBuf, "checkval2=\"%s\" ", checkval);
		strcat(record, TempBuf);

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "comment=\"keyid %s\" ", Keylog.id);
		strcat(record, TempBuf);

		strcat(record, "slot=\"0\" ");

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "id=\"%s\" ", Keylog.id);
		strcat(record, TempBuf);

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "timestamp=\"%s\" ", Keylog.timestamp);
		strcat(record, TempBuf);

		strcat(record, "device=\"Terminal\" ");

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "serialnumber=\"%s\" ", Keylog.serialnumber);
		strcat(record, TempBuf);

		strcat(record, "vendorid=\"UnionPay\"/>\r\n");

		memset(TempBuf, 0, sizeof(TempBuf));
		sprintf(TempBuf, "[%d/%d]", i+1, KeylogNum);
		ScrDisp_Api(LINE4, 0, TempBuf, FDISP|CDISP);
		Delay_Api(100);

		ret = WriteFile_Api(RUSSIA_KEYFILE_OUT, (unsigned char *)record, GetFileSize_Api(RUSSIA_KEYFILE_OUT), strlen(record));
		if (ret)
		{
			ScrClrLine_Api(LINE2, LINE6);
			ErrorPrompt("write keylog failed", 3);
			return;
		}
	}
	ret = WriteFile_Api(RUSSIA_KEYFILE_OUT, (unsigned char *)end, GetFileSize_Api(RUSSIA_KEYFILE_OUT), strlen(end));
	if (ret)
	{
		ScrClrLine_Api(LINE2, LINE6);
		ErrorPrompt("write keylog failed", 3);
		return;
	}
	
	ScrClrLine_Api(LINE2, LINE6);
	ErrorPrompt("Export success", 3);
}












