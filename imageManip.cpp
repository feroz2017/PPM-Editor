/*
    Including required libraries
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/resource.h>



#define MAX_SIZE 700
using namespace std;
/*
    Starting of main program
*/
struct pixel
{
    /* data */
    /*
        r,g,b storing image pixel values
    */
    int r,g,b = 0;
};

struct image
{
    /* 
        As images is represted as a matrix so....
    */
    pixel pic[MAX_SIZE][MAX_SIZE];
    int rows = 0;
    int columns = 0;
};
/*
    Declaring Necessary functions 
*/

/*
    loading and Saving Image
*/
void loadImage(string s,image& im);
void saveImage(string s,image& im);

/*
    Flipping Horizontal and vertical images
*/
void horizontalFlip(image& im);
void verticalFlip(image& im);

/*
    Making a copy of image's pixels
*/
void copyImage(pixel tmp[][MAX_SIZE], image &im);


/*
    Making R,G,B flatten by setting them equal to zero
*/
void flattenRed(image& im);
void flattenGreen(image& im);
void flattenBlue(image& im);

/*
    Making R,G,B negate
*/

void negateRed(image& im);
void negateGreen(image& im);
void negateBlue(image& im);


/*
    Converting image to grayscale
*/
void grayscaleConvert(image& im);

/*
    Rotating Img's Matrix through 90 degree
*/
void rotateImage(image& im);

/*
    Starting of main program
*/
int main(){

    /*
        This code is used to increase the size of stack => Soruce: Stackoverflow..
        I prefer this code over making copying statemets in make file::: reason ::: learning purpose
    */
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

    /*End of Code which increase the stack Size*/
    image img;
    string filename = "";
    int num = 0;
        cout << "\n\n";
    while(num!=12){
        // presenting menu to user  for operations
        cout << "Welcome to the image manipulation program!\n";
        cout << "The current loaded image is:" << filename;
        cout << "\n1. load image\n";
        cout << "2. save image\n";
        cout << "3. horizontal flip\n";
        cout << "4. vertical flip\n";
        cout << "5. flatten Red\n";
        cout << "6. flatten Green\n";
        cout << "7. flatten Blue\n";
        cout << "8. negate Red\n";
        cout << "9. negate Green\n";
        cout << "10. negate Blue\n";
        cout << "11. Convert to Grayscale\n";
        cout << "12. Quit\n";
        cin >> num;
         string filename2;
        switch(num)
        {
        case /* constant-expression */ 1:
            /* code */
            cout << "What file to load? ";
            cin >> filename;
            loadImage(filename,img);
            break;
        case /* constant-expression */2:
           
            cout << "Where to save file? ";
            cin >> filename2;
            saveImage(filename2,img);
            loadImage(filename,img);
            /* code */
            break;
        case /* constant-expression */3:
            horizontalFlip(img);
            /* code */
            break;
        case /* constant-expression */4:
            verticalFlip(img);
            /* code */
            break;
        case /* constant-expression */5:
            flattenRed(img);
            /* code */
            break;
        case /* constant-expression */6:
            flattenGreen(img);
            /* code */
            break;
        case /* constant-expression */7:
            flattenBlue(img);
            /* code */
            break;
        case /* constant-expression */8:
            negateRed(img);
            /* code */
            break;
        case /* constant-expression */9:
            /* code */
            negateGreen(img);
            break;
        case /* constant-expression */10:
            /* code */
            negateBlue(img);
            break;
        case /* constant-expression */11:
            /* code */
            grayscaleConvert(img);
            break;
        case /* constant-expression */12:
            /* code */
            cout << "Thank you for playing!\n\n";
            break;
        
        default:
            cout << "Invalid Input\n";
            break;
        }
    }
    return 0;
}
/*
    Definition of loading a image
*/
void loadImage(string s,image& im){
    ifstream file(s.c_str()); // Converting into to c_style image using c_str()
    if(file.fail()){
        cout << "There is an error while loading image\n";
        return;
    }
    string mg_num,width_str,height_str,range_str;

    file >> mg_num;
    if(mg_num != "P3"){
        file.close();
        cout << "This is not PPM file format.\n";
        return;
    }
    file >> width_str >> height_str >> range_str;
    im.columns = atoi(width_str.c_str()); // Storing columns
    im.rows = atoi(height_str.c_str()); // Storing Rows

    // Dummy variable for RGB
    string R,G,B;
    int count = 1;
    for (unsigned int i = 0; i < im.rows ; i++){
        for (unsigned int j = 0; j < im.columns ; j++){
            file >> R >> G >> B;
           // cout << atoi(R.c_str()) << " " << atoi(G.c_str()) << " " << atoi(B.c_str()) << " ";
            im.pic[i][j].r = atoi(R.c_str());
            im.pic[i][j].g = atoi(G.c_str());
            im.pic[i][j].b = atoi(B.c_str());
            count++;
        }
    }

    file.close();
    
        
}

void saveImage(string s,image& im){
    ofstream file(s.c_str()); // Converting into to c_style image using c_str()
    if(file.fail()){
        cout << "There is an error while loading image\n";
        return;
    }
    file << "P3\n";
    file << im.columns <<" "<< im.rows <<"\n255\n";
    // Dummy variable for RGB
    string R,G,B;
    int count = 1;
    for (unsigned int i = 0; i < im.rows ; i++){
        for (unsigned int j = 0; j < im.columns ; j++){
            
           
            int R = im.pic[i][j].r;
            int G = im.pic[i][j].g;
            int B = im.pic[i][j].b;
            file << R << " " << G << " " << B << " \n";
        }
    }

    file.close();
    
}
void horizontalFlip(image& im){
    int rows = im.rows;
    int columns = im.columns;
    for (int i = 0; i < rows; i++)
		{
			int left = 0, right = columns - 1;
			if ((columns % 2) == 0) //even flipping
			{
				while (left != (columns / 2))
				{
					pixel templeft, tempright;
					templeft = im.pic[i][left];
					tempright = im.pic[i][right];
					im.pic[i][left] = tempright;
					im.pic[i][right] = templeft;
					left++;
					right--;

				}
			}
			else if ((columns % 2) == 1)// odd number flipped
			{
				while (left != right)
				{
					pixel templeft, tempright;
					templeft = im.pic[i][left];
					tempright = im.pic[i][right];
					im.pic[i][left] = tempright;
					im.pic[i][right] = templeft;
					left++;
					right--;
				}
			}
		}
}
void verticalFlip(image& im){
    int rows = im.rows;
    int columns = im.columns;
    for (int i = 0; i < columns; i++)
		{
			int top = 0, bottom = rows - 1;
			if ((rows % 2) == 0) //even flipping
			{
				while (top != (rows / 2))
				{
					pixel temptop, tempbottom;
					temptop = im.pic[top][i];
					tempbottom = im.pic[bottom][i];
					im.pic[top][i] = tempbottom;
					im.pic[bottom][i] = temptop;
					top++;
					bottom--;

				}
			}
			else if ((rows % 2) == 1)
			{
				while (top != bottom)
				{
					pixel temptop, tempbottom;
					temptop = im.pic[top][i];
					tempbottom = im.pic[bottom][i];
				    im.pic[top][i] = tempbottom;
					im.pic[bottom][i] = temptop;
					top++;
					bottom--;
				}
			}
		}
}
void copyImage(pixel tmp[][MAX_SIZE], image &im){
     for (unsigned int i = 0; i < im.rows ; i++){
        for (unsigned int j = 0; j < im.columns ; j++){
            tmp[i][j] = im.pic[i][j];
        }
    }
}
void flattenRed(image& im){
     for (unsigned int i = 0; i < im.rows ; i++){
        for (unsigned int j = 0; j < im.columns ; j++){
            im.pic[i][j].r = 0;
        }
    }
}
void flattenGreen(image& im){
    for (unsigned int i = 0; i < im.rows ; i++){
        for (unsigned int j = 0; j < im.columns ; j++){
            im.pic[i][j].g = 0;
        }
    }
}
void flattenBlue(image& im){
    for (unsigned int i = 0; i < im.rows ; i++){
        for (unsigned int j = 0; j < im.columns ; j++){
            im.pic[i][j].b = 0;
        }
    }
}
void negateRed(image& im){
    for (unsigned int i = 0; i < im.rows ; i++){
        for (unsigned int j = 0; j < im.columns ; j++){
            if(im.pic[i][j].r == 0){
                im.pic[i][j].r = 255;
            }
            else if (im.pic[i][j].r == 255){
                im.pic[i][j].r = 0;
            }
            else{
                im.pic[i][j].r = 255 - im.pic[i][j].r;
            }
        }
    }
}
void negateGreen(image& im){
    for (unsigned int i = 0; i < im.rows ; i++){
        for (unsigned int j = 0; j < im.columns ; j++){
            if(im.pic[i][j].g == 0){
                im.pic[i][j].g = 255;
            }
            else if (im.pic[i][j].g == 255){
                im.pic[i][j].g = 0;
            }
            else{
                im.pic[i][j].g = 255 - im.pic[i][j].r;
            }
        }
    }
}
void negateBlue(image& im){
    for (unsigned int i = 0; i < im.rows ; i++){
        for (unsigned int j = 0; j < im.columns ; j++){
            if(im.pic[i][j].b == 0){
                im.pic[i][j].b = 255;
            }
            else if (im.pic[i][j].b == 255){
                im.pic[i][j].b = 0;
            }
            else{
                im.pic[i][j].b = 255 - im.pic[i][j].r;
            }
        }
    }
}
void grayscaleConvert(image& im){
  for (unsigned int i = 0; i < im.rows ; i++){
        for (unsigned int j = 0; j < im.columns ; j++){
            pixel newPixel;
            // According to give formula
            newPixel.r = (im.pic[i][j].r * 0.3) + (im.pic[i][j].g * 0.6) + (im.pic[i][j].b * 0.11);
            newPixel.g = (im.pic[i][j].r * 0.3) + (im.pic[i][j].g * 0.6) + (im.pic[i][j].b * 0.11);
            newPixel.b = (im.pic[i][j].r * 0.3) + (im.pic[i][j].g * 0.6) + (im.pic[i][j].b * 0.11);
            im.pic[i][j] = newPixel;
        }
    }   
}
