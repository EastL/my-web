
class SaveBMP
{
private:
        FILE *fp;
        unsigned int *bitmap_array;
        bool load_success;
        
	    unsigned int  bfsize;


	    unsigned int biSize;
        unsigned int biWidth;;
        unsigned int biHeight;

        unsigned int biSizeImage;

        void putint(unsigned int i, FILE* outfile)
        {
            fputc( i & 0xff , outfile);
            i >>= 8;
            fputc(i & 0xff, outfile);
            i >>= 8;
            fputc(i & 0xff, outfile);
            i >>= 8;
            fputc(i & 0xff, outfile);
       }
        void putshortint(unsigned short int i, FILE* outfile)
        {
            fputc(i & 0xff, outfile);
            i >>= 8;
            fputc(i & 0xff, outfile);
       }
        void put3byte(unsigned int i, FILE* outfile)
        {
            fputc( (i & 0xff0000)>>16 , outfile);
            fputc( (i & 0xff00)>>8, outfile);
            fputc( i & 0xff , outfile);
       }
public:
	~SaveBMP()// ok
	{
		if(load_success)
		{
			delete [] bitmap_array;
		}
	}
	void initBMP(unsigned int w,unsigned h)
	{
          biWidth=w;
          biHeight=h;
          
          if(load_success) bitmap_array = new unsigned int [w*h];
          
    }
    void put_pixel(unsigned int x,unsigned int y ,unsigned pixel)
    {
          if(load_success)
	        bitmap_array[biWidth* biHeight - (biWidth - x - 1) - y * biWidth - 1] = pixel;
    }
    SaveBMP(char *file)
    {
        fp = fopen (file,"wb");
        if(fp) load_success = true;
    }
	void Save ()
	{
		if(load_success)
		{
            //header BITMAPFILEHEADER            
            putshortint(19778,fp); // �}�YBM���� 
            
            bfsize = biWidth * biHeight * 3 + (4 - ((biWidth * 3) % 4))* biHeight + 54 ;
            //printf("%d",(4 - ((biWidth * 3) % 4))* biHeight);
            //system ("pause");
		    putint(bfsize,fp);//�����ɮפj�p  �ݭn�ק� !!! 
		    
			putint(0,fp);//�O�d 
			
			//header BITMAPINFOHEADER
			putint(54,fp); // bmp data offset
			putint(40,fp); // bmp header size
			putint(biWidth,fp);
		    putint(biHeight,fp);
		    putshortint(1,fp); //planes�ƥ� 
		    putshortint(24,fp); // pixel bit�ƥ�  
			putint(0,fp);//���Y�O�_ 
			
			//biSizeImage �ݭncheck 
			biSizeImage = biWidth * biHeight * 3 + (4 - ((biWidth * 3) % 4))* biHeight ;
			//printf("%d",(( 4 - (biWidth % 4) ) + biWidth));
			//system ("pause");
			putint(biSizeImage,fp);//�v���j�p 
			
			putint(2953,fp);//x�ѪR�� 
            putint(2953,fp);//y�ѪR��
            putint(0,fp);//�ҨϥΪ��C���`�� 
		    putint(0,fp);//���n�C��ƶq 
		    
		    //�s�J���
            for( int i=0 ;i< biWidth* biHeight ; i++)
            {
                 put3byte( bitmap_array[i],fp);
			     if( (i+1) % biWidth == 0 && (biWidth*3)%4 != 0 )
					for(unsigned int j=0 ; j<(4-(biWidth*3)%4); fputc(0,fp),j++);
             }
			fclose(fp);
        }			
     }      
};



