
#include "ShortFeatures.h"

CShortFeatures::CShortFeatures()
: CFeatures(), num_vectors(0), num_features(0), 
  feature_matrix(NULL)
{
}

CShortFeatures::~CShortFeatures()
{
  delete[] feature_matrix;
}

/// get feature vector for sample num
short int* CShortFeatures::get_feature_vector(int num, int &len, bool &free)
{
  len=num_features ; 
  if ((num<num_vectors) && feature_matrix)
    {
      free=false ;
      return &feature_matrix[num*num_features];
    } 
  else
    {
      free=true ;
      short int* feat=new short int[len] ;
      compute_feature_vector(num, feat) ;
      if (preproc)
	{
	  short int* feat2 = preproc->apply_to_feature_vector(feat, len);
	  delete[] feat ;
	  return feat2 ;
	} ;
      return feat ;
    }
}

void CShortFeatures::free_feature_vector(short int* feat, bool free)
{
  if (free)
    delete[] feat ;
} 

short int* CShortFeatures::get_feature_matrix(int &num_feat, int &num_vec)
{
  num_feat=num_features;
  num_vec=num_vectors;
  return feature_matrix;
}
