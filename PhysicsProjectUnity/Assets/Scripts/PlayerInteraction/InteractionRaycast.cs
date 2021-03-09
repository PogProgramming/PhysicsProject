using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InteractionRaycast : MonoBehaviour
{
    public LayerMask interactionLayer;
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Q))
        {
            RaycastHit hit;
            if (Physics.Raycast(Camera.main.transform.position, Camera.main.transform.forward, out hit, 4f)){
                Debug.Log(hit.transform.name);
                RaycastTrigger rt = hit.transform.GetComponent<RaycastTrigger>();
                if(rt != null)
                {
                    Debug.Log("made it here?");
                    rt.PressButton();
                }
            }
        }

    }
}
