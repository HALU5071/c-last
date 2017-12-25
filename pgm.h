/*****************************************************************************/
/*                                                                           */
/*           FILE  : pgm.h                                                   */
/*           ABOUT : pgm ファイルを読み書きするためのヘッダファイル          */
/*           DATE  : 06/04/24                                                */
/*                                                                           */
/*****************************************************************************/


/***********************************************************/
/*                         定数宣言                        */
/***********************************************************/
#define MAX_IMAGESIZE   1024 //縦・横の最大画素数
#define MAX_BRIGHTNESS   255 //最大階調値
#define GRAYLEVEL        256 //想定する階調値（最大諧調値＋１）
#define MAX_FILENAME     256 //ファイル名最大長
#define MAX_BUFFERSIZE   256 //バッファ最大長


/***********************************************************/
/*                   グローバル変数宣言                    */
/***********************************************************/
unsigned char image1[MAX_IMAGESIZE][MAX_IMAGESIZE]; //入力画像用配列
unsigned char image2[MAX_IMAGESIZE][MAX_IMAGESIZE]; //出力画像用配列
int x_size1, y_size1;                               //image1の横画素数，縦画素数
int x_size2, y_size2;                               //image2の横画素数，縦画素数


/***********************************************************/
/*                   関数プロトタイプ宣言                  */
/***********************************************************/
void load_image_data(); //画像読み込み用関数
void save_image_data(); //画像書き込み用関数


/***********************************************************/
/*                           関数                          */
/***********************************************************/
//-----------------------------------------------------------------------------
/**
 *pgm画像，横画素数，縦画素数のデータをファイルから読み込み
 *image1[][], x_size1, y_size1 にそれぞれ代入する関数
 */
void load_image_data(){

	char file_name[MAX_FILENAME]; //ファイル名用の文字配列
	char buffer[MAX_BUFFERSIZE];  //データ読み込み用作業変数
	FILE *fp;                     //ファイルポインタ
	int max_gray;                 //最大諧調値
	int x, y;                     //ループ変数

	printf("------------------------------------------------------------\n");
	printf("                モノクロ階調画像入力ルーチン                \n");
	printf("------------------------------------------------------------\n");
	printf("ファイル形式はpgm，バイナリ形式とします\n" );
	printf("入力ファイル名を入力してください(*.pgm) : ");

	/***** 入力ファイルのオープン *****/
	scanf("%s",file_name);
	fp = fopen(file_name,"rb");
	if(NULL == fp){//fpがNULLなら入力失敗

		printf( "その名前のファイルは存在しません\n" );
		exit(1);

	}

	/***** ファイルタイプ（P5）の確認 *****/
	fgets(buffer,MAX_BUFFERSIZE,fp);
	if(buffer[0] != 'P' || buffer[1] != '5'){

		printf("ファイルのフォーマットがP5とは異なります\n" );
		exit(1);

	}

	/***** x_size1, y_size1 の代入 *****/
	x_size1 = 0; //x_size1の初期化
	y_size1 = 0; //y_size1の初期化
	while(x_size1 == 0 || y_size1 == 0){

		fgets(buffer,MAX_BUFFERSIZE,fp);
		if(buffer[0] != '#')//#から始まるコメントは読み飛ばす
			sscanf(buffer,"%d %d",&x_size1,&y_size1);

	}

	/***** max_gray の代入 *****/
	max_gray = 0; //max_grayの初期化
	while( max_gray == 0 ){

		fgets(buffer,MAX_BUFFERSIZE,fp);
		if(buffer[0] != '#')//#から始まるコメントは読み飛ばす
			sscanf(buffer,"%d",&max_gray);
	}

	/***** 画面へのパラメータ表示 *****/
	printf("横の画素数 : %d\n",x_size1);
	printf("縦の画素数 : %d\n",y_size1);
	printf("最大諧調値 : %d\n",max_gray);

	/***** 読込む画像が適切かチェック *****/
	if(x_size1 > MAX_IMAGESIZE || y_size1 > MAX_IMAGESIZE){//画像の大きさが想定値以内か調べる

		printf("想定値 %d × %d を超えています\n",MAX_IMAGESIZE,MAX_IMAGESIZE);
		printf("もう少し小さい画像を使ってください\n" );
		exit(1);

	}
	if( max_gray != MAX_BRIGHTNESS){//最大諧調値が適切か調べる
		printf( "最大諧調値が不適切です\n" );
		exit(1);
	}

	/***** 画像データを読み込んで，画像用配列に代入する *****/
	for(y = 0;y < y_size1;y++)
		for( x= 0;x < x_size1;x++)
			image1[y][x] = (unsigned char)fgetc(fp);

	printf("データは正しく読み込まれました\n");
	printf("------------------------------------------------------------\n");
	fclose(fp);

}
//-----------------------------------------------------------------------------
/**
 *image2[][], x_size2, y_size2 のデータを
 *それぞれpgm画像，横画素数，縦画素数としてファイルに保存する関数
 */
void save_image_data()
{

	char file_name[MAX_FILENAME]; //ファイル名用の文字配列
	FILE *fp;                     //ファイルポインタ
	int x, y;                     //ループ変数

	printf("------------------------------------------------------------\n");
	printf("            モノクロ階調画像(pgm形式)出力ルーチン           \n");
	printf("------------------------------------------------------------\n");
	printf("出力ファイル名を入力して下さい(*.pgm) : ");

	/***** 出力ファイルのオープン *****/
	scanf("%s",file_name);
	fp = fopen(file_name,"wb");

	/***** pgm形式の為のヘッダ出力 *****/
	fputs("P5\n",fp);                            //ファイル識別子"P5"を先頭に出力
	fputs("# Created by Image Processing\n",fp); //#で始まるコメント行（省略可能）
	fprintf(fp,"%d %d\n",x_size2,y_size2);       //画像の横幅，縦幅の出力
	fprintf(fp,"%d\n",MAX_BRIGHTNESS);           //最大諧調値の出力

	/***** 画像データの出力 *****/
	for(y = 0;y < y_size2;y++)
		for(x = 0;x < x_size2;x++)
			fputc(image2[y][x],fp);

	printf( "データは正しく出力されました\n" );
	printf("------------------------------------------------------------\n");
	fclose( fp );

}
//-----------------------------------------------------------------------------
