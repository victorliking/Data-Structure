#include "scene.h"
using namespace std;

Scene::Scene(int max)
{ if(max>0)
  { 
    x= new int[max];
    y= new int[max];
    my_image=new Image*[max];
    for(int i=0;i<max;i++)
    { my_image[i]=NULL;
    }
    this->max=max;
  }   
}

Scene::Scene(const Scene & source)
{  copy(source);
}

Scene::~Scene()
{  clear();
}

const Scene & Scene::operator=(const Scene & source)
{  if(this!=&source)
   { clear();
     copy(source);
   }
   return *this;
}

void Scene::changemaxlayers(int newmax)
{  if(newmax==max) return;
   if(newmax<max)
   {  for(int i=newmax;i<max;i++)
      { if(my_image[i]!=NULL)
        cout<<"invaild newmax"<<endl;
        return ;
      }
   }
   Image **new_my_image = new Image*[newmax]; 
   int *newx = new int[newmax];
   int *newy = new int[newmax];
   
   if(newmax>max)
   {  for(int i=0;i<max;i++)
      { if(my_image[i]!=NULL)
      	{ new_my_image[i]=new Image();
     	*(new_my_image[i])=*(my_image[i]); 
      	newx[i]=x[i];
      	newy[i]=y[i];
        }
       else 
       { new_my_image[i]=NULL;
	 newx[i]=0;
   	 newy[i]=0;
       }
      }
      for(int i=max;i<newmax;i++)
      {
	new_my_image[i]=NULL;
	newx[i]=0;
   	newy[i]=0;
      }
	
   }
   else 
   {  for(int i=0;i<newmax;i++)
     { if(my_image[i]!=NULL)
      
      { new_my_image[i]=new Image();
	*(new_my_image[i])=*(my_image[i]);
	newx[i]=x[i];
	newy[i]=y[i];
      }
      else 
       { new_my_image[i]=NULL;
	 newx[i]=0;
   	 newy[i]=0;
       }
    
    }
      
   }
   clear();
   max=newmax;
   x=newx;
   y=newy;
   my_image=new_my_image;
   new_my_image=NULL;
   newx=NULL;
   newy=NULL;
}

void Scene::addpicture(const char* FileName, int index, int x ,int y)
{  
   if(index<0||index>=max)
   { cout<<"index out of bouns"<<endl;
     return; 
   }
   Image *picture= new Image();
   picture->readFromFile(FileName);
   if(my_image[index]!=NULL)
   {  delete my_image[index];
   }
   my_image[index]=picture;
   this->x[index]=x;
   this->y[index]=y;
}

void Scene::changelayer(int index, int newindex)
{  if(index==newindex)
   return;
   if(index<0||newindex>=max||newindex<0||newindex>=max)
   { cout<<"invalid index"<<endl;
     return;
   }

   if(my_image[newindex]!=NULL)
   delete my_image[newindex];
   my_image[newindex]=new Image(*(my_image[index]));
   x[newindex]=x[index];
   y[newindex]=y[index];
   x[index]=0;
   y[index]=0;
   delete my_image[index];
   my_image[index]=NULL;
}

void Scene::translate(int index,int xcoord,int ycoord)
{  if(index<0||index>=max||my_image[index]==NULL)
   {  cout<<"invalid index"<<endl;
      return;
   }
   this->x[index]=xcoord;
   this->y[index]=ycoord;
}


Image Scene::drawscene() const
{  
   int width_max=0;
   int height_max=0;
   int h=0;
   int w=0;
   for(int i=0;i<max;i++)
   {  
	if(my_image[i]!=NULL)
      
       { 
		w=my_image[i]->width();
	        h=my_image[i]->height();
	        if(width_max<x[i]+w)	
		width_max=x[i]+w;	
	        if(height_max<y[i]+h)
		height_max=y[i]+h;
      	}
   }
   
   Image new_image;  
   new_image.resize(width_max,height_max);
 



  for(int i=0;i<max;i++)
   { 
     if(my_image[i]==NULL)
     continue;
     else 
       {
        	for(int k=y[i]; k<(y[i]+my_image[i]->height()); k++)
		{   
			//cout << "Reached line 123" << endl;
			for(int j=x[i]; j<(x[i]+my_image[i]->width()); j++)
		  	{       
		     		 *new_image(j,k)=*(*my_image[i])(j-x[i],k-y[i]);
				      
					      
		  	}
		}       
	}
    

   }
   return new_image;

}


Image* Scene::getpicture(int index) const 
  {
    if(index<0 || index >=max||my_image[index]==NULL)
        {cout << "invalid index" << endl;
        return NULL;}
    else 
      {
        return my_image[index]; 
      }
   }


void Scene::clear()
{   delete [] x;
    delete [] y;
    for(int i=0;i<max;i++)
    {  delete my_image[i];
    }  
    delete [] my_image;
}

void Scene::copy(const Scene & source)
{   max=source.max;
    my_image= new Image*[max];
    x= new int[max];
    y= new int[max];
    for(int i=0;i<max;i++)
    {  if(source.my_image[i]!=NULL)
       { x[i]=(source.x)[i];
         y[i]=(source.y)[i];
         my_image[i]=new Image(*(source.my_image[i]));
       }
       else 
       { my_image[i]=NULL;
       }
    }


}


void Scene::deletepicture (int index)
{   
    	if(my_image[index]==NULL||index>=max||index<0)
    	{  cout<<"invalid index"<<endl;
          
        }
        else 
        {
        delete my_image[index];
       	my_image[index]=NULL; 
        }
   

}

