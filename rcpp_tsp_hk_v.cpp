// algorithme naif pris de https://github.com/vrunge/salesmanRcpp/blob/master/src/salesmanRcpp.cpp
//' @title monVoyageRcpp
//' @description
//' This algorithms returns the indices of towns in the shortest order for the Euclidean norm using the Held-Karp algorithm
//' @name monVoyageRcpp
//' @param towns dataframe of towns generated by the `Towns` function
//'
//' @export
// [[Rcpp::export]]
IntegerVector monVoyageRcppHK(DataFrame towns)
{
  NumericVector X = towns["X"];
  NumericVector Y = towns["Y"];
  unsigned char n = towns.nrows();
  double distance = INFINITY;
  double D;
  IntegerVector res = IntegerVector(n+1);
  res(0) = 1;
  res(n) = 1;

  unsigned char a[n-1];
  for(unsigned char i = 0; i < n-1; i++){a[i] = i+1;}

  do
  {
    D = distanceCpp(X[0],Y[0],X[a[0]],Y[a[0]]);
    for(unsigned char i = 0; i < n-2; i++)
    {D = D + distanceCpp(X[a[i]],Y[a[i]],X[a[i+1]],Y[a[i+1]]);}
    D = D + distanceCpp(X[0],Y[0],X[a[n-2]],Y[a[n-2]]);

    if(D < distance)
    {
      for(unsigned char i = 1; i < n; i++){res(i) = a[i-1] + 1;}
      distance = D;
    }

  }while(next_permutation(a, a + n-1));

  res.attr("class") = "salesman";
  return res;
}
