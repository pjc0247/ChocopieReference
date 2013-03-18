def cpInitialize
	Log.output "cpInitialize"

	puts ""
	Log.output "Initializing input processors"

	Log.output "Ime..."
	$ime = Ime.new
	Log.output "Keyboard..."
    $input = Input.new
	Log.output "Mouse..."
    $mouse = Mouse.new
	Log.output "All done"
	puts ""

	Log.output "Initializing graphic processors"

	Log.output "Graphic..."
    $graphic = Graphic.new 
	Log.output "Font..."
    $font = Font.new("cpbase\\common\\sysfont.fon",15)
	Log.output "All done"
	puts ""

	Log.output "Initializing physics processor"
	Log.output "Physics..."
	$physics = Physics.new
	Log.output "All done"
	puts ""

	Log.output "Creating manager classes"
	Log.output "EventManager..."
    $event = EventManager.new
	Log.output "SceneManager..."
    $scene = SceneManager.new

	Log.output "WindowManager..."
    $winmgr = WindowManager.new
	Log.output "SoundManager..."
    $sndmgr = SoundManager.new
	Log.output "ObjectManager..."
    $objmgr = ObjectManager.new
	Log.output "CollisionManager..."
    $colmgr = LayeredCollisionManager.new

	Log.output "TouchManager..."
    $touch = TouchManager.new
	Log.output "All done"
	puts ""
    
	Log.output "Initializing system objects"
	sysobj_add($input)
    sysobj_add($mouse)

    sysobj_add($scene)

    sysobj_add($objmgr)
    sysobj_add($colmgr)
	Log.output "done"
	puts ""

	Log.output "Creating system layers"
	Log.output "EffectLayer..."
    $layerEffect = Layer.new(Z_EFFECT)
	Log.output "InterfaceLayer..."
    $layerInterface = Layer.new(Z_UI)
	Log.output "ObjectLayer..."
    $layerObject = Layer.new(Z_OBJECT)
	Log.output "WindowLayer..."
    $layerWindow = Layer.new(Z_UI)
    $layerWindow.autoDispose = false
	Log.output "All done"
	puts ""
    
    $layerInterface.add $layerWindow

    Log.output "Chocopie Initialized"
    Log.output "Interpreter Version : #{$cp_version_major}.#{$cp_version_minor}.0"
    Log.output "CpBase      Version : #{getMajorVersion}.#{getMinorVersion}.#{getFixVersion}"
end