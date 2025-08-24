start = -140
end =  100

result = 360 - (-(-180 - start) + (180 - end))
if result > 180:
    result = -(360 - result)
elif result < -180:
    result = 360 + result

print("First: ", result)