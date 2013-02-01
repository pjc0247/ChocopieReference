# encoding:utf-8

import 'gameobject/*'
import 'gameobject/Resultbox.cp'

class Scene < SceneBase
    def initialize
        super

        @fontTitle = Font.new("c:\\windows\\fonts\\gulim.ttc", 30)
        @fontTitle.style = BOLD
        
        @fontVersion = Font.new("c:\\windows\\fonts\\gulim.ttc", 20)
        @fontVersion.style = BOLD
        
        @klassSearch = InputBox.new(10,10,150,30)
        @klassSearch.default = "Class name"
        @klassSearch.textChangedHandler = method(:klassSearch)
        
        @methodSearch = InputBox.new(165,10,180,30)
        @methodSearch.default = "Method name"
        
        @klassList = ListBox.new(10,45,140,300)
        @klassList.itemSelectedHandler = method(:klassSelected)
       
        @methodList = ListBox.new(165,45,170,300)
        @methodList.itemSelectedHandler = method(:methodSelected)
        
        @result = ResultBox.new(350,10,480,335)
        
        klassSearch(@klassSearch,nil)
    end

    def dispose
        super
    end

    def drawText(x,y,msg,font,sx,sy)
        font.color = Color.DarkGray
        font.draw(x+sx,y+sy,msg)
        font.color = Color.Black
        font.draw(x,y,msg)
    end
    def update
        crt = $graphic.size
        $graphic.color = Color.White
        $graphic.fill(0,0,crt.w,crt.h)
        
        drawText(20,356,"Chocopie Wiki",@fontTitle, 4,3)
        @fontVersion.style = BOLD
        drawText(643,345,"api version",@fontVersion, 2,1)
        @fontVersion.style = NONE
        drawText(693,366,"1.41.0",@fontVersion, 1,1)
    end
    
    def methodSelected(obj,idx)
        @result.load("data/" + @klass + "/" + obj.item[idx])
    end
    def klassSearch(obj,null)
        @klassList.clear
 
        Dir.entries("data/").each do |klass|
            if klass == '.' or klass == '..'
            elsif klass.downcase.include? obj.text.downcase
                @klassList.add klass
            end
        end
       @klassList.select = 0
    end
    def klassSelected(obj,idx)
        @methodList.clear
        
        if obj.item.size == 0
            return
        end 
        
        @klass = obj.item[idx]
        Dir.entries("data/" + obj.item[idx] + "/").each do |method|
            if method == '.' or method == '..'
            else
                @methodList.add method
            end
        end
    end
end