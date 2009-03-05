require 'yaml'
require 'rexml/document'
include REXML

file = File.new( "box.scene" );

doc = Document.new( file );
root = doc.root;

class Vector

    def initialize( x, y, z )
        @x = x;
        @y = y;
        @z = z;
    end
    
    def x=( x )
        @x = x
    end
    
    def x
        @x
    end
    
    def y
        @y
    end
    
    def y=( y )
        @y = y
    end
    
    def z
        @z
    end
    
    def z=( z )
        @z = z
    end

end

class Quaternion

    def initialize( w, x, y, z )
        @w = w;
        @x = x;
        @y = y;
        @z = z;
    end
    
    def w=( w )
        @w = w
    end
    
    def w
        @w
    end
    
    def x=( x )
        @x = x
    end
    
    def x
        @x
    end
    
    def y
        @y
    end
    
    def y=( y )
        @y = y
    end
    
    def z
        @z
    end
    
    def z=( z )
        @z = z
    end

end

class Component

    def initialize( system )
    
        @system = system
    
    end
    
    def system
        @system
    end

end

class GraphicsComponent < Component

    def initialize( ogreNode )
        @system = 'graphics';
        @model = '/data/entities/models/' + ogreNode.attributes[ 'name' ] + '.model'
    end
    
    def model
        @model
    end

end

class GeometryComponent < Component

     def initialize( ogreNode )
        @system = 'geometry';
    
        @scale = Vector.new( 0, 0, 0 );
        @position = Vector.new( 0, 0, 0 );
        @orientation = Quaternion.new( 0, 0, 0, 0 );
 
        @scale.x = ogreNode.elements[ 'scale' ].attributes[ 'x' ];
        @scale.y = ogreNode.elements[ 'scale' ].attributes[ 'y' ];
        @scale.z = ogreNode.elements[ 'scale' ].attributes[ 'z' ];
        
        @position.x = ogreNode.elements[ 'position' ].attributes[ 'x' ];
        @position.y = ogreNode.elements[ 'position' ].attributes[ 'y' ];
        @position.z = ogreNode.elements[ 'position' ].attributes[ 'z' ];
        
        @orientation.w = ogreNode.elements[ 'rotation' ].attributes[ 'qw' ];
        @orientation.x = ogreNode.elements[ 'rotation' ].attributes[ 'qx' ];
        @orientation.y = ogreNode.elements[ 'rotation' ].attributes[ 'qy' ];
        @orientation.z = ogreNode.elements[ 'rotation' ].attributes[ 'qz' ];
    end
    
    def position
        @position
    end
    
    def scale
        @scale
    end
    
    def orientation
        @orientation
    end

end

class Entity

    def initialize( ogreNode )
    
        @components = Array.new
        
        @components.push( GraphicsComponent.new( ogreNode ) );        
        @components.push( GeometryComponent.new( ogreNode ) );
        
        @name = ogreNode.attributes[ 'name' ];
        
    end
    
    def name
        @name
    end
    
    def components
        @components
    end

end

entities = Array.new;

root.each_element( "//node" ) { | node |

    entity = Entity.new( node );
    entities.push( entity );
}

levelName = ARGV[ 0 ].to_s
levelFilePath = levelName + '.yaml'

outputFile = File.new( levelFilePath,  "w+" );
outputFile.write( entities.to_yaml );
outputFile.close( );

puts 'written ' + levelName + ' to ' + levelFilePath