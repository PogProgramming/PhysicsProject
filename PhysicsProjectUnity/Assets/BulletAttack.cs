using UnityEngine;

public class BulletAttack : MonoBehaviour
{
    public float bulletDamage = 0;
    public float bulletSpeed = 0;

    public Vector3 bulletDirection;

    Vector3 origin;

    public void SetBullet(float damage, float speed, Vector3 direction)
    {
        bulletDamage = damage;
        bulletSpeed = speed;
        bulletDirection = direction;
    }

    void Start()
    {
        origin = transform.position;
        if (bulletDamage == 0 || bulletSpeed == 0) 
            Destroy(gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(bulletDirection * Time.deltaTime * bulletSpeed);
        if (Vector3.Distance(origin, transform.position) > 100f) Destroy(gameObject);
    }
}
