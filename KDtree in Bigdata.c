	#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <math.h>
    #include <stdbool.h>

    double *gendata(int num);
    int search_kdtree(int dim, int ndata,double *data,int k,int *cluster_size,int *cluster_start,double **cluster_bdry,double *query,double *res);
    void bipartition_fn(int dimensions,int nodes,int i0, int im, double *data,int *cluster_size,int *cluster_start, double *cluster_bdry, double *cluster_centroid);
    void kdtree_fn(int dimensions, int ndata, int k, double *data,int *k_cluster_size,double **k_cluster_centroid,int *k_cluster_start,double **k_cluster_bdry );
    double calculateDistance(int *cluster_visited, int cluster_counter,int *k_cluster_start,int *k_cluster_size,int dimensions, double *data, double *query, double *res);
    int visits = 0;
    int main()
    {
        int n_dimensions,m_nodes,e,f,g,mn_data;
        printf("Give any value greater than 0 for n-dimensions");
        scanf("%d",&n_dimensions);
        printf("Give any large value to generate number of points ");
        scanf("%d", &m_nodes);
        printf(" Provide input number to create number of clusters");
        scanf("%d",&f);
        mn_data = m_nodes*n_dimensions;
        double *Bigdata;
        int *kd_cluster_size;
        double **kd_cluster_centroid;
        int *kd_cluster_start;
        double **kd_cluster_bdry;
        mydata = gendata(mn_data); /*dynamic array generation for data points*/

        kd_cluster_bdry=(double **)malloc((2*f - 2)*sizeof(double *));
        for(e=0;e<(2*f-2);e++)
            *(kd_cluster_bdry+e)=(double *)malloc(2*n_dimensions*sizeof(double));
        kd_cluster_centroid=(double **)malloc((2*f-2)*sizeof(double *));
        for(e=0;e<(2*f-2);e++)
            *(kd_cluster_centroid+e)=(double *)malloc(n_dimensions*sizeof(double));
        kd_cluster_size=malloc((2*f-2)*sizeof(int));
        kd_cluster_start = malloc((2*f-2)*sizeof(int));

        /*calling the kdtree function*/
        kdtree_function(n_dimensions, mn_data, f, mydata, kd_cluster_size, kd_cluster_centroid, kd_cluster_start, kd_cluster_bdry);

        /*printing the cluster size */
      //  int sum=0;
        printf("cluster size \n");
        for(e=f-2; e<(2*f - 2); e++){
            printf("%d ", kd_cluster_size[e);
           // sum =sum+k_cluster_size[i];
        }

        free(mydata);
        free(kd_cluster_bdry);
        free(kd_cluster_centroid);
        free(kd_cluster_size);
        free(kd_cluster_start);
        return 0;
    }


    void kdtree_function(int n_dimensions, int mn_data, int f, double *data,int *k_cluster_size,double **k_cluster_centroid,int *k_cluster_start,double **k_cluster_bdry){

        int e,g,dim_0,dim_max,x,m=0,l,n=0,check=1,s,temp=0,nodes = mn_data;
        dim_0 = 0, dim_max =mn_data ;
        int *cluster_size, *cluster_start;
        double *cluster_bdry;
        double *cluster_centroid;
        double *query;
        double *res;

        query = malloc(sizeof(double)*n_dimensions);
        res = malloc(sizeof(double)*n_dimensions);
        cluster_centroid = malloc(n_dimensions*sizeof(double));
        cluster_bdry = malloc(4*n_dimensions*sizeof(double));
        cluster_size=(int*)malloc(2*sizeof(int));
        cluster_start = (int*)malloc(2*sizeof(int));

    /* iterating k-1 times to form k clusters */
        for(x=0 ; x<k-1; x++){

        bipartition_fn(dimensions, nodes, d0, dm, data, cluster_size, cluster_start, cluster_bdry, cluster_centroid);

        for( e=0;e<dimensions; e++){
        k_cluster_centroid[x][e] = cluster_centroid[e];
        }
        for( e=0;e<2; e++){
        k_cluster_size[m] = cluster_size[e];
        k_cluster_start[m] = cluster_start[];
        m++;
        }
        int p=0,r=0;
        while(p<2){
            l=0;
            e=0;
            while(e<2*dimensions){
                k_cluster_bdry[temp][l] = cluster_bdry[r];
                l++;
                e++;
                r++;
            }
            temp++;
            p++;
        }

        s = pow(2,check);


        if(x == 0 ||(x%(s-2)) == 0){
            dim_0 =0;
            nodes = k_cluster_size[n];
            check++;
            n++;
        }
        else{
            dim_0 = dim_0+k_cluster_size[n-1];
            nodes = k_cluster_size[n];
            n++;
        }
        }

         /*Searching 10 points*/
        for(x=0; x<10; x++){
                visits =0;
        for(e=0;e<dimensions;e++){
              query[e] = ((double)rand()*1001) / (double)RAND_MAX ;
        }
       // printf("query : ");
       // for(i=0;i<dimensions;i++){
       //     printf("%lf ",query[i]);
       // }
        printf("\n");
      int search =search_kdtree(n_dimensions,mn_data,mydata,f,k_cluster_size,k_cluster_start,k_cluster_bdry,query,res);
       printf ("visits: %d \n",search);
        }

        free(cluster_bdry);
        free(cluster_centroid);
        free(cluster_size);
        free(cluster_start);
    }

    /*Each bipartition function gives 2 clusters*/
    void bipartition_fn(int dimensions,int nodes,int d0, int dm, double *data,int *cluster_size,int *cluster_start, double *cluster_bdry, double *cluster_centroid){

        int e,g,x,f;
        int  node = nodes/dimensions;
        double sum,min,max;
        double *cluster_assign;
        cluster_assign = malloc(nodes*sizeof(double));
        int *assign;
        assign= malloc(node*sizeof(int));
       // printf("nodes: %d \n", nodes);

            /*calculate centroid and boundaries*/

        e=0;
        g=d0;
        while(e<dimensions){
                sum=0.0;
            while(g<(dim_0+m_nodes)){
                sum = sum+data[g];
                g = g+dimensions;
            }
        cluster_centroid[e] = sum/node;
            e = e+1;
            g=dim_0+e;
        }

        /* Calculate variance of each dimension and find dimension with maximum variance*/
         double var[n_dimensions];
         int o,h;
         h=d0;
         o=0;
        while(o<n_dimensions){
            sum = 0.0;
            while(h<(dim_0+m_nodes)){
               sum = sum +((cluster_centroid[o] - mydata[h])*(cluster_centroid[g] - mydata[h]));
               h=h+dimensions;
            }
            var[o] = sum/node;
            o=o+1;
            h=(dim_0+o);
        }
        double large = var[0];
        int max_dimension =0;
        int p;
        for(p=0; p<dimensions; p++){
            if(var[p]>large){
                large = var[p];
                max_dimension = p;
            }
       }

       /* find mean of maximum variance*/
        double mean = cluster_centroid[max_dimension];
        //printf("mean %lf \n",mean);

        /* Assigning 0's to the points less than mean and 1's for the points greater than mean*/
        e=d0+max_dimension;
        x=0;
        while(i<(d0+nodes)){
            if(data[i] < mean){
               assign[x]=0;
            }
            else{
                assign[x]=1;
            }
            x++;
            i= i+dimensions;
        }

        /* Rearranging the points based on assign array points lesser than mean goes to left and greater than mean goes to right*/
        x=0;
        int count=0;
        int y=0;
        for(i=0; i<node; i++){
            if(assign[y] == 0){
                    count++;
                for(j=dimensions*i; j<dimensions*(i+1); j++){

                    cluster_assign[x] = data[d0+j];
                    x++;
                }
            }
            y++;
        }
        cluster_size[0] = count*dimensions;
        cluster_start[0]= dim_0;

        count=0;
        y=0;
        for(i=0; i<node; i++){
            if(assign[y]!=0){
                count++;
                for(j=dimensions*i; j<dimensions*(i+1); j++){
                    cluster_assign[x] = data[dim_0+j];
                    x++;
                }
            }
            y++;
        }
        cluster_size[1] = count*dimensions;
        cluster_start[1]= dim_0+cluster_size[0];

        x=0;
        for(i=dim_0; i< dim_0+nodes; i++){
        data[i] = cluster_assign[x];
        x++;
        }

        /* Calculate cluster boundaries for the 2 clusters that are formed from above partition*/
        x=0;
        p=0;
        while(p<2){
            j=cluster_start[p];
            i=0;
            while(i<dimensions){
                min=data[j];
                max=data[j];
                while(j < (cluster_start[p]+cluster_size[p])){

                    if(data[j]<min)
                        min = data[j];
                    if(data[j]>max)
                        max= data[j];
                    j = j+dimensions;
                }
                cluster_bdry[x]=min;
                x=x+1;
                cluster_bdry[x]=max;
                x=x+1;
                i = i+1;
                j=cluster_start[p]+i;
            }
            p++;
        }

        free(cluster_assign);
        free(assign);

    }

    int search_kdtree(int dimensions, int ndata,double *data,int k,int *k_cluster_size,int *k_cluster_start,double **k_cluster_bdry,double *query,double *res){
    int i,j,l,cluster_visited[k],counter =0,count=0, flag=0;
    double y,distance,calcDistance,min,clu_min_distance[k];

    int cluster_counter =0;


    for( i= k-2; i< (2*k -2); i++ ){
        calcDistance =0.0;
        l=0;
        for(j=0;j<dimensions;j++){
            if(query[j] < k_cluster_bdry[i][l]){
                calcDistance += pow(fabs(query[j]-k_cluster_bdry[i][l]),2);
            }
            else if(query[j] > k_cluster_bdry[i][l+1]){
                 calcDistance += pow(fabs(query[j]-k_cluster_bdry[i][l]),2);
            }
            else{
                ;
            }
            l=l+2;
        }
        if(flag == 0){
            min = calcDistance;
            cluster_visited[cluster_counter] = i;
        }
        if(min > calcDistance){
            min = calcDistance;
            cluster_visited[cluster_counter] = i;
        }
        calcDistance = sqrt(calcDistance);
        clu_min_distance[count] = calcDistance;
        count++;
        flag++;
    }
    printf(" \n");

    /* calculates minimum distance from search point to all the points in the cluster which has nearest boundary*/
    distance = calculateDistance(cluster_visited, cluster_counter,k_cluster_start, k_cluster_size, dimensions,data,query,res);

    /* calculates the closest point distance to the search point from all the clusters*/
    double distance1;
    for(i=0; i<k; i++){
        if((distance > clu_min_distance[i] ) && ((i+k-2) != cluster_visited[0])){
            cluster_counter++;
            cluster_visited[cluster_counter] = i+k-2;
            distance1 = calculateDistance(cluster_visited, cluster_counter,k_cluster_start, k_cluster_size, dimensions, data, query, res);
            if(distance > distance1){
                distance = distance1;
            }
        }
    }
    printf(" Nearest distance : %lf \n", distance);
    return visits;
    }

    /* Calculates the Nearest distance from search point to all the points in selected cluster */

    double calculateDistance(int *cluster_visited, int cluster_counter,int *k_cluster_start,int *k_cluster_size,int dimensions,double *data, double *query, double *res){
        int y = cluster_visited[cluster_counter];
        int i, j, x,m;
        int node = k_cluster_size[y];
        double sum =0.0;
        int count=0;
        double distance1;
        for(i= k_cluster_start[y]; i< (k_cluster_start[y] + node); i=i+dimensions){
            x=0;
            visits++;
            for(j=0; j<(dimensions); j++){
                sum = sum + pow(fabs((data[i+j] - query[x])),2);
                x++;
            }
            count++;
            sum = sqrt(sum);
            if(count == 1){
                distance1 = sum;
            }
            if(distance1 > sum ){
                distance1 = sum;
            }
            }
        return distance1;
    }


    /*Initialize data array*/
    double *gendata(int num)
    {
        double *ptr = malloc(num*sizeof(double));
        int j = 0;
        if(ptr != NULL)
        {
            for(j = 0; j < num; j++)
            {
                ptr[j] = ((double)rand()*1001) / (double)RAND_MAX;
            }
        }
        return ptr;
    }