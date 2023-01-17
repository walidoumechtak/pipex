int main()
{
  int fd[2];
  pipe(fd);
  int idp = fork();
  int arr[] = {0,1,2,3,4,5,6,7,8,9};
  int len = sizeof(arr) / sizeof(int);
  int start;
  int end;
  
  if (idp == 0)
  {
    start = 0;
    end = len / 3;  
  }
  else{
    int idp2 = fork();
    if (idp2 == 0)
    {
      start = len / 3;
      end = len / 3 + 3;
    }
    else
    {
      start = len / 3 + 3;
      end = len;
    }
  }

  int sum = 0;
  while (start < end)
  {
    sum += arr[start];
    start++;
  }
  printf("sum of each process is : %d\n", sum);
  while (wait(NULL) != -1);
  return (0);
}
