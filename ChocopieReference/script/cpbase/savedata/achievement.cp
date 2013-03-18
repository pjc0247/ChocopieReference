import 'cpbase/savedata/savedata.cp'

class Achievement < SaveData
	def initialize(path = "data\\achievement.dat")
		super(path)
	end
end
