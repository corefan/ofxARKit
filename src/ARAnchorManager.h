//
//  ARAnchor.h
//  GeoBeats
//
//  Created by Joseph Chow on 8/18/17.
//

#ifndef ARAnchor_h
#define ARAnchor_h

#include "ofMain.h"
#include <vector>
#include <ARKit/ARKit.h>
#include "ARUtils.h"
#include "ARObjects.h"
using namespace ARObjects;
namespace ARCore {
    typedef std::shared_ptr<class ARAnchorManager>AnchorManagerRef;
    
    //! Helper class to deal with anchors
    class ARAnchorManager {
        
        //! Stores data of all currently found planes.
        std::vector<PlaneAnchorObject> planes;
        
        //! reference to all currently found or added regular anchors
        std::vector<ARObject> anchors;
        
        //! The number of anchors currently found
        NSInteger anchorInstanceCount;
        
        //! The session to draw from
        ARSession * session;
        
        //! camera object to help draw the anchors
        ofCamera camera;
        
    public:
        ARAnchorManager();
        ARAnchorManager(ARSession * session);
        
        //! Flag for whether or not planes should be updated
        bool shouldUpdatePlanes;
        
        //! Adds an anchor based on the current position of the camera - basically at (0,0) with a slight z offset.
        void addAnchor();
        
        //! adds an anchor at the specified position.
        void addAnchor(ofVec2f position);
        
        //! adds an ARObject to be tracked by ARKit.
        void addAnchor(ARObject anchor);
        
        static AnchorManagerRef create(ARSession * session){
            if(!session){
                NSLog(@"Error - AnchorManagerRef requires an ARSession object");
            }else{
                return AnchorManagerRef(new ARAnchorManager(session));
            }
        }
        
        //! Returns the vector of currently found planes
        std::vector<PlaneAnchorObject> getPlaneAnchors(){
            return planes;
        }
        
        //! Allows you to loop through the anchors and do something
        //! with each anchor. Pass in a lambda function
        void loopAnchors(std::function<void(ARObject)> func);
        
        //! Allows you to loop through planes and do something with each plane
        void loopPlaneAnchors(std::function<void(PlaneAnchorObject)> func);
        
        //! Returns the PlaneAnchorObject associated with found planes
        PlaneAnchorObject getPlaneAt(int index=0);
        
        //! Toggles whether or not planes should be updated at each iteration.
        void togglePlaneUpate(){
            shouldUpdatePlanes = !shouldUpdatePlanes;
        }
        
        //! same as above but removes the anchor directly from the ARSession instance.
        //! Note that it does not remove a corresponding ARObject though, but simply removes
        //! stuff directly from the session in an effort to provide another way to remove ARKit added objects.
        void removeAnchorDirectly(int index=0);
        
        //! clears all existing plane anchors being tracked.
        void clearPlaneAnchors();
        void removePlane(NSUUID * anchorId);
        void removePlane(int index=0);
        
        
        //! Clears all existing anchors
        void clearAnchors();
        
        //! removes anchor with the specified uuid
        void removeAnchor(NSUUID * anchorId);
        
        //! removes the anchor with the specified index.
        void removeAnchor(int index=0);
        
        //! Get the number of planes detected.
        int getNumPlanes();
        
        void drawPlanes(ARCommon::ARCameraMatrices cameraMatrices);
        
        // general update function
        void update();
        
        // update function for dealing with planes.
        void updatePlanes();
        
    };
}

#endif /* ARAnchor_h */
