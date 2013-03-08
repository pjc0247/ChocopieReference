###################################################
#             ChocoPie GameEngine                 #
#                           Scene Base            #
###################################################

class SceneBase < Object
    #attr_accessor :_dispose

    def initialize
        @id = 0
        
        #@_dispose = []
		$scene.iv.each do |key,value|
			puts "retain " + key.to_s
			instance_variable_set(key,value)
			instance_variable_get(key).retain = $scene.rc[key]
        end
    end
    def dispose
		super
    end

    def event(e,arg)
        if e == QUIT
            
        end
    end

    def update
        
    end
end


# 게임에 사용할 Scene은 SceneBase로부터 상속받아 사용합니다.
class Scene < SceneBase
end
