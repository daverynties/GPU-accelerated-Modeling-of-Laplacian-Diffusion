#helper function used to create a time-series scatterplot representation
#   of current element temperatures
setwd('C:\\Users\\user\\Desktop\\677\\Heat-Equation\\Heat-Equation\\plotla')

#graph and save each scatterplot created at all times
for (cat in unique(heatEquationDataSmallerSuper$Time)){
  d <- subset(heatEquationDataSmallerSuper, Time == cat)
  attach(d)
  plot(Element, Temperature, main="Element Temperatures", 
       xlab="Element[i] ", ylab="Temperature ", pch=19)
   string <- paste(cat, ".png")
   dev.copy(png, string)
   dev.off()
  
}


