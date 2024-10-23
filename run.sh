echo "Now it will ask for month for which you need to calculate the expenses"
echo "Months : Jan, Feb, Apr, Mar, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec"
rm -rf a.out 

rm -rf output.txt

#In place of PhonePe_Statement_Jul2024_Oct2024.pdf write your phonpe transaction detail pdf name  
pdftotext -layout PhonePe_Statement_Jul2024_Oct2024.pdf output.txt 
g++ main.cpp 
./a.out 

