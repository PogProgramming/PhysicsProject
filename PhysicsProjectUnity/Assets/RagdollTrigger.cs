using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RagdollTrigger : MonoBehaviour
{

    private void OnTriggerEnter(Collider other)
    {
        Ragdoll r = other.gameObject.GetComponentInParent<Ragdoll>();
        if(r != null)
        {
            r.RagdollOn = true;
        }
    }
}
