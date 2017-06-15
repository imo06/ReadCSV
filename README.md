# ReadCSV
For reading in csv files into C++. 

# How to use
ReadCSV uses the first line of the file as the header information and reads in line-by-line the csv file. It assumes that all the headers are named in the first line. Missing data will cause problems on that line and will not be read properly.

Initialize `ReadCSV` using the filename, deliminator, and (optionally) an array of `char`'s you wish to ignore. The file is automatically read in and the header map populated. The headers can be obtained using `GetHeaderNames()`. 

You can read through the file line-by-line. The `ReadLine()` function will read the next line in and return `True` if the line exists. This includes empty lines.

The raw string of the line can be obtained using `GetLine()`. Use this if you wish to sift through the line using your own method.

The template function `GetValue<T>(headerName)` can be used to get the current line's value for Header Name `headerName` as a `T` value.

#Example of Use
Below is an example
```
char removeChars[] = "()-\" ";
read::ReadCSV csv(fileName, ',');
while(csv.ReadLine()){
            csv.GetValue<std::string>("Header1");
            csv.GetValue<double>("Value");
}
```

#Error Handling
If the file cannot be open, an `std::string` message is thrown.



# To Do List:
* Allow for ignoring lines off the top 
* Allow for unnamed headers
* Deal with missing data
* Deal with cells that have comma's as part of their formatting
* Deal with '(' as negative numbers (e.g. from excel)
