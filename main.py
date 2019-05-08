import detector

print("特征值检测:",detector.token("A","C"))    
print("LCS检测:",detector.text("A.cpp","C.cpp"))
print("最大权流检测:",detector.graph("C","A"))
print("属性检测:",detector.attribute("A.cpp","C.cpp")) 
print("")
print("特征值检测:",detector.token("B","D"))
print("LCS检测:",detector.text("B.cpp","D.cpp"))
print("最大权流检测:",detector.graph("D","B"))
print("属性检测:",detector.attribute("B.cpp","D.cpp"))

