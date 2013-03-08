class RootObject
	def dispose
		disposeAll
	end

	def disposeAll
        self.instance_variables.each do |v|
            rv = instance_variable_get(v)
            if rv.methods.member?(:dispose) == true and
                rv.retain <= 0
				#			p rv.methods.sort
                puts "auto disposing : " + v
                rv.dispose
            end
        end
    end
end