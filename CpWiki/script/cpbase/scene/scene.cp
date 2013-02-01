###################################################
#             ChocoPie GameEngine                 #
#                           Scene Base            #
###################################################

class SceneBase
    #attr_accessor :_dispose

    def initialize
        @id = 0
        
        #@_dispose = []
    end
    def dispose
        ## 씬이 종료되면 씬에 포함된 모든 객체를 dispose한다.
        disposeAll
    end

    def event(e,arg)
        if e == QUIT
            
        end
    end

    def update
        
    end

    # 씬에 포함된 모든 dispose가능한 멤버들을 dispose 해줍니다.
    def disposeAll
        self.instance_variables.each do |v|
            rv = instance_variable_get(v)

            if rv.methods.member?("dispose") == true and
                rv.retain <= 0
                puts "auto disposing : " + v
                rv.dispose
            end
        end
    end
end


# 게임에 사용할 Scene은 SceneBase로부터 상속받아 사용합니다.
class Scene < SceneBase
end
