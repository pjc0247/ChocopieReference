def checkVersion
    scriptVersion = getVersion
    linkedVersion = getLinkedVersion

    if scriptVersion.major != linkedVersion.major
        return false
    elsif scriptVersion.minor != linkedVersion.minor
        return false
    elsif scriptVersion.fix != linkedVersion.fix
        return false
    else
        return true
    end
end

def cpInitialize
    
    if checkVersion == false
        Log.output "스크립트 버전과 링크된 버전이 일치하지 않습니다."
    end

	$ime = Ime.new
    $input = Input.new
    $mouse = Mouse.new
    $graphic = Graphic.new 
    $font = Font.new("cpbase\\common\\sysfont.fon",15)
    
    $event = EventManager.new
    $scene = SceneManager.new

    $winmgr = WindowManager.new
    $sndmgr = SoundManager.new
    $objmgr = ObjectManager.new
    $colmgr = LayeredCollisionManager.new

    $touch = TouchManager.new

    sysobj_add($input)
    sysobj_add($mouse)

    sysobj_add($scene)

    sysobj_add($objmgr)
    sysobj_add($colmgr)
    

    $layerEffect = Layer.new(Z_EFFECT)
    $layerInterface = Layer.new(Z_UI)
    $layerObject = Layer.new(Z_OBJECT)
    $layerWindow = Layer.new(Z_UI)
    
    $layerInterface.add $layerWindow

    $physics = Physics.new

    puts "cp initialized "
    puts "cpver : major " + $cp_version_major.to_s + " minor " + $cp_version_minor.to_s
end