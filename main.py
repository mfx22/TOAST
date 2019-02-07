# ToastBot python code
# Used for Raspberry Pi on ToastBot
# Michael Xiao and Katie Bradford

# Takes input of weather, image, or sketch and sends commands to PIC32 to operate motors

from PIL import Image
from gpiozero import LED, Button
import time
from weather import Weather, Unit
import sys

out = LED(23)
switch = LED(24)
switch.off()
out.off()


if __name__ == "__main__":
    mode = sys.argv[1]
if mode == 'weather':
   
    weather   = Weather(unit=Unit.FAHRENHEIT)
    location  = weather.lookup_by_location('ithaca')
    forecasts = location.forecast

    print(forecasts[0].text)
    print(forecasts[0].date)
    print(forecasts[0].high)
    print(forecasts[0].low)

    temperature = int(forecasts[0].high)
    condition   = forecasts[0].text

    data = [0]*100

    tens = temperature/10
    ones = temperature%10

    # Degrees sign
    data[8]=1
    
    #First Number
    if tens == 1:
      data[2] = 1
      data[12]=1
      data[22]=1
      data[32]=1
      data[42]=1
      
    elif tens == 2: 
      data[0]=1
      data[1]=1
      data[2]=1
      data[12]=1
      data[22]=1
      data[21]=1
      data[20]=1
      data[30]=1
      data[40]=1
      data[41]=1
      data[42]=1
      
    elif tens == 3:
      data[0]=1
      data[1]=1
      data[2]=1
      data[12]=1
      data[22]=1
      data[21]=1
      data[32]=1
      data[42]=1
      data[41]=1
      data[40]=1

    elif tens == 4:
      data[0]=1
      data[10]=1
      data[20]=1
      data[21]=1
      data[22]=1
      data[12]=1
      data[2]=1
      data[32]=1
      data[42]=1
      
    elif tens == 5:
      data[0]=1
      data[1]=1
      data[2]=1
      data[10]=1
      data[22]=1
      data[21]=1
      data[20]=1
      data[32]=1
      data[40]=1
      data[41]=1
      data[42]=1
      
    elif tens == 6:
      data[0]=1
      data[1]=1
      data[2]=1
      data[10]=1
      data[22]=1
      data[21]=1
      data[20]=1
      data[32]=1
      data[40]=1
      data[41]=1
      data[42]=1
      data[30]=1

    elif tens == 7:
      data[0]=1
      data[1]=1
      data[2]=1
      data[12]=1
      data[22]=1
      data[32]=1
      data[42]=1
      
    elif tens == 8:
      data[0]=1
      data[1]=1
      data[2]=1
      data[10]=1
      data[12]=1
      data[22]=1
      data[21]=1
      data[20]=1
      data[32]=1
      data[40]=1
      data[41]=1
      data[42]=1
      data[30]=1
      
    elif tens == 9:
      data[0]=1
      data[1]=1
      data[2]=1
      data[10]=1
      data[12]=1
      data[22]=1
      data[21]=1
      data[20]=1
      data[32]=1
      data[42]=1
      
    elif tens == 0:
      data[0]=1
      data[1]=1
      data[2]=1
      data[10]=1
      data[12]=1
      data[22]=1
      data[20]=1
      data[32]=1
      data[40]=1
      data[41]=1
      data[42]=1
      data[30]=1
    # Second number


    if ones == 1:
      data[6] = 1
      data[16]=1
      data[26]=1
      data[36]=1
      data[46]=1
      
    elif ones == 2: 
      data[4]=1
      data[5]=1
      data[6]=1
      data[16]=1
      data[26]=1
      data[25]=1
      data[24]=1
      data[34]=1
      data[44]=1
      data[45]=1
      data[46]=1
  
    elif ones == 3:
      data[4]=1
      data[5]=1
      data[6]=1
      data[16]=1
      data[26]=1
      data[25]=1
      data[36]=1
      data[46]=1
      data[45]=1
      data[44]=1

    elif ones == 4:
      data[4]=1
      data[14]=1
      data[24]=1
      data[25]=1
      data[26]=1
      data[16]=1
      data[6]=1
      data[36]=1
      data[46]=1
  
    elif ones == 5:
      data[4]=1
      data[5]=1
      data[6]=1
      data[14]=1
      data[26]=1
      data[25]=1
      data[24]=1
      data[36]=1
      data[44]=1
      data[45]=1
      data[46]=1
  
    elif ones == 6:
      data[4]=1
      data[5]=1
      data[6]=1
      data[14]=1
      data[26]=1
      data[25]=1
      data[24]=1
      data[36]=1
      data[44]=1
      data[45]=1
      data[46]=1
      data[34]=1

    elif ones == 7:
      data[4]=1
      data[5]=1
      data[6]=1
      data[16]=1
      data[26]=1
      data[36]=1
      data[46]=1
      
    elif ones == 8:
      data[4]=1
      data[5]=1
      data[6]=1
      data[14]=1
      data[16]=1
      data[26]=1
      data[25]=1
      data[24]=1
      data[36]=1
      data[44]=1
      data[45]=1
      data[46]=1
      data[34]=1
      
    elif ones == 9:
      data[4]=1
      data[5]=1
      data[6]=1
      data[14]=1
      data[16]=1
      data[26]=1
      data[25]=1
      data[24]=1
      data[36]=1
      data[46]=1
      
    elif ones == 0:
      data[4]=1
      data[5]=1
      data[6]=1
      data[14]=1
      data[16]=1
      data[26]=1
      data[24]=1
      data[36]=1
      data[44]=1
      data[45]=1
      data[46]=1
      data[34]=1
    # Conditions

    if condition.find('sun'):
      data[61]=1
      data[62]=1
      data[63]=1
      data[73]=1
      data[83]=1
      data[82]=1
      data[81]=1
      data[71]=1
  
    elif condition.find('cloud'):
      data[62]=1
      data[63]=1
      data[71]=1
      data[72]=1
      data[73]=1
      data[74]=1
      data[75]=1
  
    elif condition.find('rain'):
      data[62]=1
      data[63]=1
      data[71]=1
      data[72]=1
      data[73]=1
      data[74]=1
      data[75]=1
      data[82]=1
      data[84]=1
      data[93]=1
      data[95]=1
      
    elif condition.find('snow'):
      data[61]=1
      data[72]=1
      data[70]=1
      data[81]=1

    elif condition.find('windy'):
      data[90]=1
      data[91]=1
      data[92]=1
      data[72]=1
      data[83]=1
      data[75]=1
      data[76]=1
      data[77]=1
      data[57]=1
      data[68]=1

elif mode == 'image':
    im=Image.open("Downloads/circle.gif")
    im.show()
    #print(im)
    im = im.resize((10,10))
    #print(im.size)
    im.save("1","PNG")
    im = im.convert('RGB')

    data = []
    count = 0

    w, h = im.size

    for x in range(h):
        for y in range(w):
            r,g,b = im.getpixel((y,x))
            if(r+g+b) >  400:
                data.append(0)
            else:
                data.append(1)


#print image and send it to 
print(data[0:10])
print(data[10:20])
print(data[20:30])
print(data[30:40])
print(data[40:50])
print(data[50:60])
print(data[60:70])
print(data[70:80])
print(data[80:90])
print(data[90:100])

switch.on()
time.sleep(1)


for x in data[:]:
    if x == 1:
        out.on()
    else:
        out.off()
    time.sleep(.02)
    
out.off()
#button = Button(23)

#while(button.is_pressed):
#    time.sleep(1)
#print('done')
#switch.off()
#out.off()
#switch.off()
