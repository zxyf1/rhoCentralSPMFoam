Info << "define the sub-indicator" << endl;
int fi = 0;
if (((dy-d) > 0.0) && ((dx)- d) > 0.0){
   fi = 1;
}else if ( ((dy-d) == 0.0) && ((dx - d) == 0.0)){
   fi = 0;
}else{
   fi = -2;
}
//If fi is positive, will be inside the wall; fi < 0 will be outside the wall; fi = 0 will be on the wall


