class ChocopieObject
	@@autoDispose = true
	@@keepList = Array.new

	def self.auto_dispose(flag)
		if flag == :true
			@@autoDispose = true
		elsif flag == :false
			@@autoDispose = false
		end
	end
	def self.keep(*args)
		args.each do |v|
			@@keepList.push ("@"+v.to_s).to_sym
		end
	end

	def initialize
	end

	def dispose
		if @@autoDispose == true
			disposeAll
		end
	end

	def disposeAll
        self.instance_variables.each do |v|
            rv = instance_variable_get(v)
            if rv.methods.member?(:dispose) == true and
                rv.retain <= 0 and
				not @@keepList.member? v

				#			p rv.methods.sort
                #puts "auto disposing : " + self.to_s + "  " + v
                rv.dispose
            end
        end
    end
end