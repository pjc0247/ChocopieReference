###################################################
#             ChocoPie GameEngine                 #
#                           Sound                 #
###################################################

LOOP = true

class Sound < Sound_
    def self.new(music,loop=false)
        $sndmgr.add self
        return super(music,loop)
    end
    def dispose
        super
        $sndmgr.delete self
    end
end
