#1/bin/sh
#Top 10 popular names from /etc/passwd file

awk -F: 'BEGIN{
n=0 
}
{
split($5, a, " ");
if(f[a[1]] <= 0){
    names[n] = a[1];
    n++;
} 
f[a[1]]++;
#print a[1]
}
END{
for(i=0;i<n;i++){
    printf("%s -> %d\n", names[i], f[names[i]]);
}
}
' /etc/passwd | sort -r -k3n | head
