###################################################
#             ChocoPie GameEngine                 #
#                           Scene Manager         #
###################################################

#2012 05 14 - 씬 뒤로가기 추가

class SceneManager
    attr_reader :scene
	attr_reader :iv, :rc

    @@stack = Stack.new

    def initialize
        @scene = nil
        @old_scene = nil
    end
    def dispose
        @@stack.clear
    end

    def change(to)
        @iv = {}
        @rc = {}

        if @scene != nil    
            @scene.dispose

            @scene.instance_variables.each do |v|
                if @scene.instance_variable_get(v).retain != 0
                    @scene.instance_variable_get(v).retain -= 1

                    @iv[v] = @scene.instance_variable_get(v)
                    @rc[v] = @scene.instance_variable_get(v).retain
                end
#if @scene.instance_variable_get(v).retain >= 0

#                end
            end
        else
            
        end

        @@stack.push(to)

        Debug.protect("scene - change") do
            import 'cpbase/scene/sceneClear.cp'
            import 'scene/' + to + '.cp'
            @scene = Scene.new

            $input.update

            puts "scene change : " + to
        end    

        $keySkip = true    
    end

    def back
        @@stack.pop
		
        if @@stack.top == nil
            puts "씬 뒤로가기 불가능"
        else
            change @@stack.top
        end
    end


    def event(e,arg)
        if @scene != nil
            @scene.event(e,arg)
        end
    end
    def update
        if @scene != nil
            @scene.update
        end
    end
end

