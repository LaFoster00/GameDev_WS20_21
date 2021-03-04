# GameDev_WS20_21

Expect for basic code from The Cherno's OpenGlSeries, all code (Rendering, Callbacks, Editor(Imgui), Seperation of Engine and Editor, GameObjects system, Data flow etc.) is done 100% by me(except for obj importer and other small features).

Select Buildconfig Release- / DebugImgui in order to get the project working correctly. Otherwise imgui will be excluded from the engine causing the editor to fail as it is depended on the feature to be implemented!

Supported file formats for the object importer are .obj (Triangulated!)
Shader can be added at will and only need to include the Attributes for Location, TexCoords and Normal (see Basic.shader)

File endings are not relevant for any files.

Camera and GameObjects can only be moved through the inspector and i strongly advise agains deleting the camera as i didnt get to implenenting a camera spawn feature.

Texture setting is implemented but i didnt get to implenting the Outliner for material settings and texture import.

Serialization is done through nlohmann::json and even though it isnt abstracted away, i tried to keep it as expandable as possible. But this part still needs a lot of work before it is where i want it to be.

Mutlithreading was planed for Rendering but had to be scrapped for now cause of time reasons.
